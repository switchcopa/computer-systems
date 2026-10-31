
#include <stdint.h>
#include <string.h>
#include "svm.h"
#include "svm_insns.h"

insn_t insn_table[NINSTRUCTIONS] = {
    { halt,    1, 0x0 }, { nop,     1, 0x1 },
    { cmovxx,  2, 0x2 }, { irmovq, 10, 0x3 },
    { rmmovq, 10, 0x4 }, { mrmovq, 10, 0x5 },
    { opq,     2, 0x6 }, { jxx,     9, 0x7 },
    { call,    9, 0x8 }, { ret,     1, 0x9 }, 
    { pushq,   2, 0xA }, { popq,    2, 0xB }
};

static bool mv_regs(cpu_t *cpu, uint64_t *rp_0, uint64_t *rp_1)
{
    uint8_t reg_ops = cpu->ir[REG_OPS_BYTE];
    
    if (rp_0 != nullptr) {

        uint8_t r0 = reg_ops >> 4;
        if (r0 >= NREGS)
            goto ins;

        *rp_0 = cpu->regs[r0];
    }

    if (rp_1 != nullptr) {
        uint8_t r1 = reg_ops & 0xF;

        if (r1 >= NREGS)
            goto ins;
        *rp_1 = cpu->regs[r1];
    }

    return true;
ins:
    cpu->stat = INS;
    return false;
}


void halt(cpu_t *cpu)
{
    cpu->stat = HLT;
}

void nop(cpu_t *cpu)
{ }

void irmovq(cpu_t *cpu)
{
    uint8_t reg = (uint8_t)cpu->ir[REG_OPS_BYTE] & 0xF;
    if (reg >= NREGS) {
        cpu->stat = INS;
        return;
    }

    uint64_t imm;
    memcpy(&imm, &cpu->ir[IMM_MEM_MOVE_BYTE], sizeof(uint64_t));
    cpu->regs[reg] = imm;
}

void rmmovq(cpu_t *cpu)
{
    uint8_t src = cpu->ir[REG_OPS_BYTE] >> 4;
    uint8_t reg_addr = cpu->ir[REG_OPS_BYTE] & 0xF;
    if (src >= NREGS || reg_addr >= NREGS) {
        cpu->stat = INS;
        return;
    }

    uint64_t disp;
    uint64_t val = cpu->regs[src];
    uint64_t addr = cpu->regs[reg_addr];

    memcpy(&disp, &cpu->ir[IMM_MEM_MOVE_BYTE], sizeof(uint64_t));
    ASSERT_VALID_ADDRESS(cpu, addr, 0x8 + disp);
    memcpy((uint8_t *)&cpu->dmem[addr] + disp, &val, sizeof(uint64_t));
}

void mrmovq(cpu_t *cpu)
{
    uint8_t op_byte = cpu->ir[REG_OPS_BYTE];

    uint8_t r0 = op_byte >> 4;
    uint8_t r1 = op_byte & 0xF;

    if (r0 >= NREGS || r1 >= NREGS) {
        cpu->stat = INS;
        return;
    }

    uint64_t disp;
    uint64_t addr = cpu->regs[r1];
    memcpy(&disp, &cpu->ir[IMM_MEM_MOVE_BYTE], sizeof(uint64_t));

    ASSERT_VALID_ADDRESS(cpu, addr, 0x8 + disp);
    memcpy(&cpu->regs[r0], 
            (uint8_t *)&cpu->dmem[addr] + disp, sizeof(uint64_t));
}

void opq(cpu_t *cpu)
{
    uint8_t op_byte = (uint8_t)cpu->ir[REG_OPS_BYTE];
    
    uint8_t r0 = op_byte >> 4;
    uint8_t r1 = op_byte & 0xF;
    if (r0 >= NREGS || r1 >= NREGS) {
        cpu->stat = INS;
        return;
    }

    uint64_t res;
    uint64_t reg_a = cpu->regs[r0];
    uint64_t reg_b = cpu->regs[r1];
    uint8_t of, zf, sf;

    switch ((cpu->ir[OP_FN_BYTE] & 0xF)) {
    case OP_ADD:
        of = __builtin_add_overflow(reg_a, reg_b, &res);
        break;
    case OP_SUB:
        of = __builtin_sub_overflow(reg_b, reg_a, &res);
        break;
    case OP_AND:
        res = reg_a & reg_b;
        of ^= of;
        break;
    case OP_XOR:
        res = reg_a ^ reg_b;
        of ^= of;
        break;
    default:
        cpu->stat = INS;
        return;
    }

    zf = (uint8_t)(res == 0u) << 2;
    sf = (uint8_t)((int64_t)res < 0) << 1;
    cpu->cc = (of | zf | sf);
    cpu->regs[r1] = res;
}

void jxx(cpu_t *cpu)
{
    uint64_t dest;
    uint8_t sf, zf;

    memcpy(&dest, &cpu->ir[JMP_ADDR_BYTE], sizeof(uint64_t));
    ASSERT_VALID_ADDRESS(cpu, dest, 0x0);
    
    sf = cpu->cc & CC_SF;
    zf = cpu->cc & CC_ZF;

    uint64_t old_rip = cpu->rip;
    switch ((cpu->ir[OP_FN_BYTE] & 0xF)) {
    case BRANCH_CASE_NONE: BRANCH_CASE_CMOV(true, dest, cpu->rip); break;
    case BRANCH_CASE_LE: BRANCH_CASE_CMOV((zf || sf), dest, cpu->rip); break;
    case BRANCH_CASE_L: BRANCH_CASE_CMOV((sf && !zf), dest, cpu->rip); break;
    case BRANCH_CASE_E: BRANCH_CASE_CMOV((zf && !sf), dest, cpu->rip); break;
    case BRANCH_CASE_NE: BRANCH_CASE_CMOV((!zf), dest, cpu->rip); break;
    case BRANCH_CASE_GE: BRANCH_CASE_CMOV((!sf || zf), dest, cpu->rip); break;
    case BRANCH_CASE_G: BRANCH_CASE_CMOV((!sf && !zf), dest, cpu->rip); break;
    default:
        cpu->stat = INS;
        return;
    }

    cpu->jmp_changed_rip = (old_rip != cpu->rip);
}

void cmovxx(cpu_t *cpu)
{
    uint8_t id_r1 = (uint8_t)cpu->ir[REG_OPS_BYTE] & 0xF;
    
    uint64_t r0, r1;
    if (!mv_regs(cpu, &r0, &r1))
        return;

    uint8_t sf, zf;
    sf = cpu->cc & CC_SF;
    zf = cpu->cc & CC_ZF;

    switch ((cpu->ir[OP_FN_BYTE] & 0xF)) {
    case BRANCH_CASE_NONE: BRANCH_CASE_CMOV(true, r0, r1); break;
    case BRANCH_CASE_LE: BRANCH_CASE_CMOV((zf || sf), r0, r1); break;
    case BRANCH_CASE_L: BRANCH_CASE_CMOV((sf && !zf), r0, r1); break;
    case BRANCH_CASE_E: BRANCH_CASE_CMOV((zf && !sf), r0, r1); break;
    case BRANCH_CASE_NE: BRANCH_CASE_CMOV((!zf), r0, r1); break;
    case BRANCH_CASE_GE: BRANCH_CASE_CMOV((!sf || zf), r0, r1); break;
    case BRANCH_CASE_G: BRANCH_CASE_CMOV((!sf && !zf), r0, r1); break;
    default:
        cpu->stat = INS;
        return;
    }

    cpu->regs[id_r1] = r1;
}

void call(cpu_t *cpu)
{
    uint64_t addr;
    int64_t sp = (int64_t)cpu->regs[REG_RSP];
    uint64_t ret_addr = cpu->rip + insn_table[0x8].len;

    ASSERT_VALID_ADDRESS(cpu, sp, -0x8);
    memcpy(&addr, &cpu->ir[JMP_ADDR_BYTE], sizeof(uint64_t));
    memcpy((uint8_t *)&cpu->dmem[sp] - 0x8, &ret_addr, sizeof(uint64_t));

    cpu->jmp_changed_rip = true;
    cpu->regs[REG_RSP] = sp - 0x8;
    cpu->rip = addr;
}

void ret(cpu_t *cpu)
{
    int64_t sp = (int64_t)cpu->regs[REG_RSP];
    ASSERT_VALID_ADDRESS(cpu, sp, 0x8);

    memcpy(&cpu->rip, &cpu->dmem[sp], sizeof(uint64_t));
    cpu->jmp_changed_rip = true;
    cpu->regs[REG_RSP] = sp + 0x8;
}

void pushq(cpu_t *cpu)
{
    int64_t sp = (int64_t)cpu->regs[REG_RSP];
    ASSERT_VALID_ADDRESS(cpu, sp, -0x8);

    uint64_t reg;
    if (!mv_regs(cpu, &reg, nullptr))
        return;

    memcpy((uint8_t *)&cpu->dmem[sp] - 0x8, &reg, sizeof(uint64_t));
    cpu->regs[REG_RSP] = sp - 0x8;
}

void popq(cpu_t *cpu)
{
    int64_t sp = (int64_t)cpu->regs[REG_RSP];
    ASSERT_VALID_ADDRESS(cpu, sp, 0x8);

    uint8_t reg = cpu->ir[REG_OPS_BYTE] >> 4;
    if (reg >= NREGS) {
        cpu->stat = INS;
        return;
    }

    memcpy(&cpu->regs[reg], &cpu->dmem[sp], sizeof(uint64_t));
    cpu->regs[REG_RSP] = sp + 0x8;
}

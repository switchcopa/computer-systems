
#ifndef SVM_H
#define SVM_H

#define KB64 65536
#define NREGS 15
#define NINSTRUCTIONS 0xC
#define INSN_LENGTH 10
#define REG_RSP 0x4

#define REG_OPS_BYTE 0x1
#define JMP_ADDR_BYTE 0x1
#define IMM_MEM_MOVE_BYTE 0x2

#define RSP_INIT 0x5000
#define RIP_INIT 0x0000

#include <stdint.h>

enum status : uint8_t
{
    AOK = 0,
    HLT,
    ADR,
    INS,
};

#define OP_FN_BYTE 0x0
#define OP_ADD 0
#define OP_SUB 1
#define OP_AND 2
#define OP_XOR 3

#define CC_OF 0b001
#define CC_SF 0b010
#define CC_ZF 0b100

#define BRANCH_CASE_NONE 0x0
#define BRANCH_CASE_LE   0x1
#define BRANCH_CASE_L    0x2
#define BRANCH_CASE_E    0x3
#define BRANCH_CASE_NE   0x4
#define BRANCH_CASE_GE   0x5
#define BRANCH_CASE_G    0x6

#define BRANCH_CASE_CMOV(condition, src, dest) do { \
    (dest) = (condition) ? (src) : (dest);          \
} while (false)

#define ASSERT_VALID_ADDRESS(cpu, addr, inc) do {  \
    if ((addr) >= KB64 || (addr) < 0         \
                || (addr) + (inc) >= KB64) { \
        cpu->stat = ADR;                     \
        return;                              \
    }                                        \
} while (false)

#define CHECK_CPU_HEALTH(cpu) do { \
    if ((cpu)->stat != AOK) \
        return;             \
} while (false)

struct cpu_t;

typedef struct cpu_t {
    uint8_t  dmem[KB64];
    uint8_t  ir[INSN_LENGTH];
    uint64_t regs[NREGS];
    uint64_t rip;

    uint8_t cc;
    enum status stat;
    bool jmp_changed_rip;

    struct insn_t {
        void (*handler)(struct cpu_t *);
        uint8_t len;
        uint8_t spec;
    } curr_insn;
} cpu_t;

typedef struct insn_t insn_t;
   
enum status run_cpu(struct cpu_t *cpu);

#endif

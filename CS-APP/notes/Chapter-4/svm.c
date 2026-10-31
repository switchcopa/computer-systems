
/* compile with GCC, C23 */

#include "svm.h"
#include "svm_insns.h"
#include <stdint.h>
#include <string.h>

void fetch(cpu_t *cpu);
void decode(cpu_t *cpu);
void execute(cpu_t *cpu);

void fetch(cpu_t *cpu)
{
    CHECK_CPU_HEALTH(cpu);
    if (cpu->rip >= KB64) {
        cpu->stat = ADR;
        return;
    }

    uint8_t insn_spec = cpu->dmem[cpu->rip] >> 4;
    uint8_t insn_len = insn_table[insn_spec].len;

    if (cpu->rip + insn_len >= KB64){
        cpu->stat = ADR;
        return;
    }

    memcpy(&cpu->ir, &cpu->dmem[cpu->rip], insn_len);
}

void decode(cpu_t *cpu)
{
    CHECK_CPU_HEALTH(cpu);
    uint8_t spec = (uint8_t)*cpu->ir >> 4;
    if (spec >= NINSTRUCTIONS) {
        cpu->stat = INS;
        return;
    }

    cpu->curr_insn = insn_table[spec];
}

void execute(cpu_t *cpu)
{
    CHECK_CPU_HEALTH(cpu);
    void (*handler)(cpu_t *) = cpu->curr_insn.handler;
    handler(cpu);
}

enum status run_cpu(cpu_t *cpu)
{
    while (cpu->stat == AOK) {
        fetch(cpu);
        decode(cpu);
        execute(cpu);

        if (cpu->jmp_changed_rip) {
            cpu->jmp_changed_rip = false;
            continue;
        }

        cpu->rip += (cpu->stat == AOK) ? cpu->curr_insn.len : 0;
    }

    return cpu->stat;
}

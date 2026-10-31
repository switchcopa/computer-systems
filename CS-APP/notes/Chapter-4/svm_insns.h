
#ifndef SVM_INSNS_H
#define SVM_INSNS_H

#include "svm.h"

void halt(cpu_t *cpu);
void nop(cpu_t *cpu);
void irmovq(cpu_t *cpu);
void rmmovq(cpu_t *cpu);
void mrmovq(cpu_t *cpu);
void opq(cpu_t *cpu);
void jxx(cpu_t *cpu);
void cmovxx(cpu_t *cpu);
void call(cpu_t *cpu);
void ret(cpu_t *cpu);
void pushq(cpu_t *cpu);
void popq(cpu_t *cpu);

extern insn_t insn_table[];

#endif

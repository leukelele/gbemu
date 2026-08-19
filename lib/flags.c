#include "flags.h"
#include "cpu.h"

void flag_set(struct cpu *cpu, uint8_t mask, bool condition) {
    if (condition) cpu->regs.af.byte.lo |= mask;
    else cpu->regs.af.byte.lo &= (uint8_t)~mask;
}

bool flag_get(const struct cpu *cpu, uint8_t mask) {
    return (cpu->regs.af.byte.lo & mask) == mask;
}

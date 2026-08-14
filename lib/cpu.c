#include "cpu.h"

void cpu_init(struct cpu *cpu, struct bus *bus) {
    cpu->bus = bus;
    reg_init(&cpu->regs);
}

uint8_t fetch(struct cpu *cpu) {
    return bus_read8(cpu->bus, cpu->regs.pc++);
}

const struct instruction *decode(uint8_t opcode) {
    return &get_instruction_table()[opcode];
}

uint8_t execute(struct cpu *cpu, const struct instruction *inst) {
    if (inst->execute) inst->execute(cpu);
    return inst->mach_cycles;
}

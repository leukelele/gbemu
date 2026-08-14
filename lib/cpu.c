#include "cpu.h"

void cpu_init(struct cpu *cpu, struct bus *bus) {
    cpu->bus = bus;
    reg_init(&cpu->regs);
}

uint8_t fetch(struct cpu *cpu) {
    return bus_read8(cpu->bus, cpu->regs.pc++);
}

// WIP
uint8_t decode(void) {
    return 0x00;
}

// WIP
uint8_t execute(void) {
    return 0x00;
}

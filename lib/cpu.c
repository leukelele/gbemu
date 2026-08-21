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

uint8_t execute(struct cpu *cpu, const struct instruction *inst,
                        uint8_t opcode) {
    if (!inst->execute) return 0x0;
    bool branched = inst->execute(cpu, opcode);
    return inst->mach_cycles + (branched ? inst->cond_cycles : 0);
}

uint8_t cpu_step(struct cpu *cpu) {
    uint8_t opcode = fetch(cpu);
    const struct instruction *inst = decode(opcode);
    return execute(cpu, inst, opcode);
}

uint8_t reg8_get(struct cpu *cpu, uint8_t index) {
    switch (index) {
        case 0: return cpu->regs.bc.byte.hi;                    // B
        case 1: return cpu->regs.bc.byte.lo;                    // C
        case 2: return cpu->regs.de.byte.hi;                    // D
        case 3: return cpu->regs.de.byte.lo;                    // E
        case 4: return cpu->regs.hl.byte.hi;                    // H
        case 5: return cpu->regs.hl.byte.lo;                    // L
        case 6: return bus_read8(cpu->bus, cpu->regs.hl.pair);  // (HL)
        case 7: return cpu->regs.af.byte.hi;                    // A
        default: return 0;
    }
}

void reg8_set(struct cpu *cpu, uint8_t index, uint8_t value) {
    switch (index) {
        case 0: cpu->regs.bc.byte.hi = value; break;                    // B
        case 1: cpu->regs.bc.byte.lo = value; break;                    // C
        case 2: cpu->regs.de.byte.hi = value; break;                    // D
        case 3: cpu->regs.de.byte.lo = value; break;                    // E
        case 4: cpu->regs.hl.byte.hi = value; break;                    // H
        case 5: cpu->regs.hl.byte.lo = value; break;                    // L
        case 6: bus_write8(cpu->bus, cpu->regs.hl.pair, value); break;  // (HL)
        case 7: cpu->regs.af.byte.hi = value; break;                    // A
        default: break;
    }
}

uint16_t reg16_get(struct cpu *cpu, uint8_t index) {
    return 0;
}
void reg16_set(struct cpu *cpu, uint8_t index, uint8_t value) {
    switch(index){
        case 0: cpu->regs.bc.pair = value; break;
        case 1: cpu->regs.de.pair = value; break;
        case 2: cpu->regs.hl.pair = value; break;
        default: cpu->regs.af.pair = value & 0xFFF0; break; 
    }
}

void stack_push16(struct cpu *cpu, uint16_t value) {
    bus_write8(cpu->bus, --cpu->regs.sp, (uint8_t)(value >> 8));
    bus_write8(cpu->bus, --cpu->regs.sp, (uint8_t)(value & 0xFF));
}

uint16_t stack_pop16(struct cpu *cpu){
    uint8_t lo = bus_read8(cpu->bus, cpu->regs.sp++);
    uint8_t hi = bus_read8(cpu->bus, cpu->regs.sp++);
    return (uint16_t)((hi << 8) | lo);
}


#include "cpu.h"

void cpu_init(struct cpu *cpu, struct bus *bus) {
    cpu->bus = bus;
    reg_init(&cpu->regs);
}

/**
 * The function is basically a wrapper for the CPU struct and its bus 
 * connection. This progresses the program counter (PC)
 *
 * @param[in] cpu It is the CPU's bus which is to be read along with the
 *                current register pointer.
 * @return The address found at the program counter.
 */
static uint8_t fetch(struct cpu *cpu) {
    return bus_read8(cpu->bus, cpu->regs.pc++);
}

/**
 * Essentially an instruction table lookup wrapper. It's more for 
 * conceptualization.
 *
 * @param[in] opcode The opcode to be translated.
 * @return The particular instruction struct that the opcode translates to.
 */
static const struct instruction *decode(uint8_t opcode) {
    return &get_instruction_table()[opcode];
}

/**
 * Checking that the instruction routine exists, executes the instruction
 * routine.
 *
 * @param[in] cpu This is for the CPU's registers
 * @param[in] inst The instruction struct itself contains the means for 
 *                 executing that particular instruction.
 * @return The machine cycles as this is the only way to know how long the
 *         instruction will execute.
 */
static uint8_t execute(struct cpu *cpu, const struct instruction *inst) {
    if (!inst->execute) return 0x0;
    bool branched = inst->execute(cpu);
    return inst->mach_cycles + (branched ? inst->cond_cycles : 0);
}

uint8_t cpu_step(struct cpu *cpu) {
    uint8_t opcode = fetch(cpu);
    const struct instruction *inst = decode(opcode);
    return execute(cpu, inst);
}

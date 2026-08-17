#include "instruction_set.h"
#include "cpu.h"

static struct instruction inst_table[INSTRUCTION_TABLE_SIZE];

static uint8_t exec_nop(struct cpu *cpu) {
    return inst_table[0x00].mach_cycles;
}
static uint8_t exec_ld_bc_indirect_a(struct cpu *cpu) {
    bus_write16(cpu->bus, fetch(cpu), cpu->regs.bc.reg);
    return inst_table[0x02].mach_cycles;
}

/**
 * Populates a single inst_table entry for the given opcode
 */
static void init_inst(uint8_t opcode, enum inst_fmt format, 
                        uint8_t operand_size, uint8_t mach_cycles,
                        uint8_t cond_cycles, inst_exec executor) {
    // struct fields may be init using designated initializers (.field = value)
    inst_table[opcode] = (struct instruction) {
        .format = format,
        .operand_size = operand_size,
        .mach_cycles = mach_cycles,
        .cond_cycles = cond_cycles,
        .execute = executor,
    };
} // init_inst()

void instruction_set_init(void) {
    init_inst(0x00, NOP, 0, 1, 0, exec_nop);
    init_inst(0x02, LD, 0, 2, 0, exec_ld_bc_indirect_a);
} // instruction_set_init()

const struct instruction *get_instruction_table(void) {
    return inst_table;
} // get_instruction_table

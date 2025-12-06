#include "instruction_set.h"

static instruction instruction_table[INSTRUCTION_TABLE_SIZE];

static void exec_nop(void) {}
static void exec_ld_bc_indirect_a(void) {}

static void init_inst(uint8_t opcode, inst_fmt format, uint8_t operand_size,
                       uint8_t mach_cycles, uint8_t cond_cycles,
                       inst_exec executor) {
    instruction_table[opcode] = (instruction){
        .opcode = opcode,
        .format = format,
        .operand_size = operand_size,
        .mach_cycles = mach_cycles,
        .cond_cycles = cond_cycles,
        .execute = executor,
    };
}

void instruction_set_init(void) {
    init_inst(0x00, NOP, 0, 1, 0, exec_nop);
    init_inst(0x02, LD, 0, 8, 0, exec_ld_bc_indirect_a);
}

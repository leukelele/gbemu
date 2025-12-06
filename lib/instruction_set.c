#include "instruction_set.h"

static instruction instruction_table[INSTRUCTION_TABLE_SIZE];

static void exec_nop(void) {}
// for "indirect" meaning see docs/dev-log.md##251205###2252
static void exec_ld_bc_indirect_a(void) {}

/**
 * populates a single instruction_table entry for the given opcode
 */
static void init_inst(uint8_t opcode, inst_fmt format, uint8_t operand_size,
                       uint8_t mach_cycles, uint8_t cond_cycles,
                       inst_exec executor) {
    // struct fields may be init using designated initializers (.field = value)
    // see docs/dev-log.md##251205###2139
    instruction_table[opcode] = (instruction){
        .opcode = opcode,
        .format = format,
        .operand_size = operand_size,
        .mach_cycles = mach_cycles,
        .cond_cycles = cond_cycles,
        .execute = executor,
    };
} // init_inst()

void instruction_set_init(void) {
    init_inst(0x00, NOP, 0, 1, 0, exec_nop);
    init_inst(0x02, LD, 0, 8, 0, exec_ld_bc_indirect_a);
} // instruction_set_init()

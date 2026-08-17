#include "instruction_set.h"
#include "cpu.h"

static struct instruction inst_table[INSTRUCTION_TABLE_SIZE];

static bool exec_nop(struct cpu *cpu) {
    return false;
}

static bool exec_ld_bc_indirect_a(struct cpu *cpu) {
    bus_write8(cpu->bus, cpu->regs.bc.pair, cpu->regs.af.byte.hi);
    return false;
}

static bool exec_pop_from_stack16(struct cpu *cpu){
    cpu->regs.bc.byte.lo = bus_read8(cpu->bus, cpu->regs.sp++);
    cpu->regs.bc.byte.hi = bus_read8(cpu->bus, cpu->regs.sp++);
    return false;
}

static bool exec_push_to_stack16(struct cpu *cpu) {
    bus_write8(cpu->bus, --cpu->regs.sp, cpu->regs.bc.byte.hi);
    bus_write8(cpu->bus, --cpu->regs.sp, cpu->regs.bc.byte.lo);
    return false;
}

/**
 * Populates a single inst_table entry for the given opcode
 */
static void init_inst(uint8_t opcode, enum inst_fmt format, 
                        uint8_t mach_cycles, uint8_t cond_cycles,
                        inst_exec executor) {
    // struct fields may be init using designated initializers (.field = value)
    inst_table[opcode] = (struct instruction) {
        .format = format,
        .mach_cycles = mach_cycles,
        .cond_cycles = cond_cycles,
        .execute = executor,
    };
} // init_inst()

void instruction_set_init(void) {
    init_inst(0x00, NOP, 1, 0, exec_nop);
    init_inst(0x02, LD, 2, 0, exec_ld_bc_indirect_a);
    init_inst(0xC1, POP, 3, 0, exec_pop_from_stack16);
    init_inst(0xC5, PUSH, 4, 0, exec_push_to_stack16);
} // instruction_set_init()

const struct instruction *get_instruction_table(void) {
    return inst_table;
} // get_instruction_table

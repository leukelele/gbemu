#include "instruction_set.h"
#include "cpu.h"

static struct instruction inst_table[INSTRUCTION_TABLE_SIZE];

/**
 * populates a single inst_table entry for the given opcode
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

/****************************************************************************
 * The following section are static functions that exectue the expected     *
 * routine of an instrunction. This is going to be alot...                  *
 ****************************************************************************/
/***************************
 * load instructions       *
 ***************************/

// LD r,r' block (0x40-0x7F, except 0x76=HALT)
static bool exec_ld_r_r(struct cpu *cpu, uint8_t opcode) {
    uint8_t dst = (opcode >> 3) & 0x7;
    uint8_t src = opcode & 0x7;
    reg8_set(cpu, dst, reg8_get(cpu, src));
    return false;
}

static bool exec_ld_r_n(struct cpu *cpu, uint8_t opcode) {
    uint8_t dst = (opcode >> 3) & 0x7;
    uint8_t src = fetch(cpu);
    reg8_set(cpu, dst, src);
    return false;
}

static bool exec_ld_indirect_a(struct cpu *cpu, uint8_t opcode) {
    uint8_t pair = (opcode >> 4) & 0x3;
    bool load = (opcode >> 3) & 0x1;

    uint16_t addr = (pair == 0) ? cpu->regs.bc.pair
                    : (pair == 1) ? cpu->regs.de.pair
                    :               cpu->regs.hl.pair;
    if (load) cpu-> regs.af.byte.hi = bus_read8(cpu->bus, addr);
    else      bus_write8(cpu->bus, addr, cpu->regs.af.byte.hi);

    if (pair == 2) cpu->regs.hl.pair++;
    else if (pair == 3) cpu->regs.hl.pair--;

    return false;
}

static bool exec_ld_rr_nn(struct cpu *cpu, uint8_t opcode) {
    uint8_t lo = fetch(cpu);
    uint8_t hi = fetch(cpu);
    uint16_t nn = (uint16_t)((hi << 8) | lo);

    switch ((opcode >> 4) & 0x3) {
        case 0: cpu->regs.bc.pair = nn; break;
        case 1: cpu->regs.de.pair = nn; break;
        case 2: cpu->regs.hl.pair = nn; break;
        case 3: cpu->regs.sp      = nn; break;
    }
    return false;
}

static bool exec_ldh(struct cpu *cpu, uint8_t opcode) {
    bool load = (opcode >> 4) & 0x1;
    bool c_operand = (opcode >> 1) & 0x1;
    uint8_t lo = c_operand ? cpu->regs.bc.byte.lo : fetch(cpu);
    uint16_t addr = (uint16_t)(0xFF00 + lo);

    if (load) cpu->regs.af.byte.hi = bus_read8(cpu->bus, addr);
    else      bus_write8(cpu->bus, addr, cpu->regs.af.byte.hi);
    return false;
}

static bool exec_pop_from_stack16(struct cpu *cpu, uint8_t opcode){
    cpu->regs.bc.byte.lo = bus_read8(cpu->bus, cpu->regs.sp++);
    cpu->regs.bc.byte.hi = bus_read8(cpu->bus, cpu->regs.sp++);
    return false;
}

static bool exec_push_to_stack16(struct cpu *cpu, uint8_t opcode) {
    bus_write8(cpu->bus, --cpu->regs.sp, cpu->regs.bc.byte.hi);
    bus_write8(cpu->bus, --cpu->regs.sp, cpu->regs.bc.byte.lo);
    return false;
}

/******************************
 * miscellaneous instructions
 ******************************/
static bool exec_nop(struct cpu *cpu, uint8_t opcode) {
    return false;
}

/****************************************************************************
 * init functions for populating the instruction table.                     *
 ****************************************************************************/
static void instruction_ld(void) {

    // LD rr,nn block: 0x01,0x11,0x21,0x31
    for (uint8_t pair = 0; pair < 4; pair++) {
        init_inst((uint8_t)(0x01 | (pair << 4)), LD, 3, 0, exec_ld_rr_nn);
    }

    // 0x02, 0x12, 0x22, 0x32; 0x0A, 0x1A, 0x2A, 0x3A
    for (uint8_t pair = 0; pair < 4; pair++) {
        init_inst((uint8_t)(0x02 | (pair << 4)), LD, 2, 0, exec_ld_indirect_a);
        init_inst((uint8_t)(0x0A | (pair << 4)), LD, 2, 0, exec_ld_indirect_a);
    }

    // 0x06, 0x16, 0x26, 0x36; 0x0e, 0x1e, 0x2e, 0x3e
    for (uint8_t pair = 0; pair < 4; pair++) {
        init_inst((uint8_t)(0x06 | (pair << 4)), LD, 2, 0, exec_ld_r_n);
        init_inst((uint8_t)(0x0e | (pair << 4)), LD, 2, 0, exec_ld_r_n);
    }

    // LD r,r' block (0x40-0x7F, except 0x76=HALT)
    for (uint16_t opcode = 0x40; opcode <= 0x7F; opcode++) {
        if (opcode == 0x76) continue;   // this particular opcode is for HALT,
                                        // which is obv not a LD instruction
        uint8_t dst = (uint8_t)((opcode >> 3) & 0x7);
        uint8_t src = (uint8_t)(opcode & 0x7);
        uint8_t cycles = (dst == 6 || src == 6) ? 2 : 1;
        init_inst((uint8_t)opcode, LD, cycles, 0, exec_ld_r_r);
    }

    init_inst(0xF0, LDH, 3, 0, exec_ldh);
    init_inst(0xE0, LDH, 3, 0, exec_ldh);
    init_inst(0xF2, LDH, 2, 0, exec_ldh);
    init_inst(0xE2, LDH, 2, 0, exec_ldh);


    init_inst(0xC1, POP, 3, 0, exec_pop_from_stack16);
    init_inst(0xC5, PUSH, 4, 0, exec_push_to_stack16);
}

void instruction_set_init(void) {
    init_inst(0x00, NOP, 1, 0, exec_nop);
    instruction_ld();
} // instruction_set_init()

const struct instruction *get_instruction_table(void) {
    return inst_table;
} // get_instruction_table

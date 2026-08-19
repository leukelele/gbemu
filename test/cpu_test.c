#include "unity.h"
#include "cpu.h"
#include "instruction_set.h"

void test_fetch_reads_byte_and_advances_pc(void) {
    struct bus bus = {0};
    struct cpu cpu;
    cpu_init(&cpu, &bus);
    cpu.regs.pc = 0xC000;

    bus_write8(&bus, cpu.regs.pc, 0x42);
    uint16_t pc_before = cpu.regs.pc;

    uint8_t value = fetch(&cpu);

    TEST_ASSERT_EQUAL_UINT8(0x42, value);
    TEST_ASSERT_EQUAL_UINT16(pc_before + 1, cpu.regs.pc);
}

void test_decode_returns_correct_metadata_for_nop(void) {
    instruction_set_init();
    const struct instruction *inst = decode(0x00);

    TEST_ASSERT_EQUAL(NOP, inst->format);
    TEST_ASSERT_EQUAL_UINT8(1, inst->mach_cycles);
    TEST_ASSERT_NOT_NULL(inst->execute);
}

void test_decode_returns_correct_metadata_for_ld_bc_indirect_a(void) {
    instruction_set_init();
    const struct instruction *inst = decode(0x02);

    TEST_ASSERT_EQUAL(LD, inst->format);
    TEST_ASSERT_EQUAL_UINT8(2, inst->mach_cycles);
    TEST_ASSERT_NOT_NULL(inst->execute);
}

void test_decode_returns_null_execute_for_unimplemented_opcode(void) {
    instruction_set_init();
    const struct instruction *inst = decode(0x03); // not yet populated

    TEST_ASSERT_NULL(inst->execute);
}

void test_execute_nop_returns_mach_cycles(void) {
    instruction_set_init();
    struct bus bus = {0};
    struct cpu cpu;
    cpu_init(&cpu, &bus);

    uint8_t cycles = execute(&cpu, decode(0x00), 0x00);
    TEST_ASSERT_EQUAL_UINT8(1, cycles);
}

void test_execute_ld_bc_indirect_a_writes_a_to_bc_address(void) {
    instruction_set_init();
    struct bus bus = {0};
    struct cpu cpu;
    cpu_init(&cpu, &bus);

    cpu.regs.bc.pair = 0xC010;      // arbitrary WRAM address
    cpu.regs.af.byte.hi = 0x99;     // register A

    uint8_t cycles = execute(&cpu, decode(0x02), 0x02);

    TEST_ASSERT_EQUAL_UINT8(0x99, bus_read8(&bus, 0xC010));
    TEST_ASSERT_EQUAL_UINT8(2, cycles);
}

void test_execute_unimplemented_opcode_returns_zero(void) {
    instruction_set_init();
    struct bus bus = {0};
    struct cpu cpu;
    cpu_init(&cpu, &bus);

    uint8_t cycles = execute(&cpu, decode(0xD3), 0xD3);

    TEST_ASSERT_EQUAL_UINT8(0, cycles);
}

void test_cpu_step_nop_advances_pc_by_one(void) {
    instruction_set_init();
    struct bus bus = {0};
    struct cpu cpu;
    cpu_init(&cpu, &bus);

    bus_write8(&bus, cpu.regs.pc, 0x00);
    uint16_t pc_before = cpu.regs.pc;

    uint8_t cycles = cpu_step(&cpu);

    TEST_ASSERT_EQUAL_UINT16(pc_before + 1, cpu.regs.pc);
    TEST_ASSERT_EQUAL_UINT8(1, cycles);
}

void test_cpu_step_ld_rr_nn_loads_hl(void) {
    instruction_set_init();
    struct bus bus = {0};
    struct cpu cpu;
    cpu_init(&cpu, &bus);
    cpu.regs.pc = 0xC000;

    bus_write8(&bus, 0xC000, 0x21);
    bus_write8(&bus, 0xC001, 0x34);
    bus_write8(&bus, 0xC002, 0x12);

    uint8_t cycles = cpu_step(&cpu);

    TEST_ASSERT_EQUAL_UINT16(0x1234, cpu.regs.hl.pair);
    TEST_ASSERT_EQUAL_UINT16(0xC003, cpu.regs.pc);
    TEST_ASSERT_EQUAL_UINT16(3, cycles);
}

void test_cpu_step_ld_r_n_loads_register(void) {
    instruction_set_init();
    struct bus bus = {0};
    struct cpu cpu;
    cpu_init(&cpu, &bus);
    cpu.regs.pc = 0xC000;

    bus_write8(&bus, 0xC000, 0x06);
    bus_write8(&bus, 0xC001, 0x5A);

    uint8_t cycles = cpu_step(&cpu);

    TEST_ASSERT_EQUAL_UINT16(0x5A, cpu.regs.bc.byte.hi);
    TEST_ASSERT_EQUAL_UINT16(2, cycles);
}

void test_cpu_step_ld_bc_indirect_a_writes_memory_and_advances_pc_by_one(void) {
    instruction_set_init();
    struct bus bus = {0};
    struct cpu cpu;
    cpu_init(&cpu, &bus);
    cpu.regs.pc = 0xC000;

    bus_write8(&bus, cpu.regs.pc, 0x02);
    uint16_t pc_before = cpu.regs.pc;
    cpu.regs.bc.pair = 0xC020;
    cpu.regs.af.byte.hi = 0x7B;

    uint8_t cycles = cpu_step(&cpu);

    // guards specifically against the earlier bug's shape: an accidental
    // extra fetch() call inside the handler would advance pc by 2 here
    TEST_ASSERT_EQUAL_UINT16(pc_before + 1, cpu.regs.pc);
    TEST_ASSERT_EQUAL_UINT8(0x7B, bus_read8(&bus, 0xC020));
    TEST_ASSERT_EQUAL_UINT8(2, cycles);
}

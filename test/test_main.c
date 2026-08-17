#include "unity.h"

// setUp and tearDown are required, even if empty
void setUp(void) {}
void tearDown(void) {}

void test_reg_init_sets_default_values(void);


void test_vram_round_trip(void);
void test_echo_ram_mirrors_wram(void);
void test_rom_stub_reads_zero(void);

void test_fetch_reads_byte_and_advances_pc(void);
void test_decode_returns_correct_metadata_for_nop(void);
void test_decode_returns_correct_metadata_for_ld_bc_indirect_a(void);
void test_decode_returns_null_execute_for_unimplemented_opcode(void);
void test_execute_nop_returns_mach_cycles(void);
void test_execute_ld_bc_indirect_a_writes_a_to_bc_address(void);
void test_execute_unimplemented_opcode_returns_zero(void);
void test_cpu_step_nop_advances_pc_by_one(void);
void test_cpu_step_ld_bc_indirect_a_writes_memory_and_advances_pc_by_one(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_reg_init_sets_default_values);


    RUN_TEST(test_vram_round_trip);
    RUN_TEST(test_echo_ram_mirrors_wram);
    RUN_TEST(test_rom_stub_reads_zero);

    RUN_TEST(test_fetch_reads_byte_and_advances_pc);
    RUN_TEST(test_decode_returns_correct_metadata_for_nop);
    RUN_TEST(test_decode_returns_correct_metadata_for_ld_bc_indirect_a);
    RUN_TEST(test_decode_returns_null_execute_for_unimplemented_opcode);
    RUN_TEST(test_execute_nop_returns_mach_cycles);
    RUN_TEST(test_execute_ld_bc_indirect_a_writes_a_to_bc_address);
    RUN_TEST(test_execute_unimplemented_opcode_returns_zero);
    RUN_TEST(test_cpu_step_nop_advances_pc_by_one);
    RUN_TEST(test_cpu_step_ld_bc_indirect_a_writes_memory_and_advances_pc_by_one);

    return UNITY_END();
}

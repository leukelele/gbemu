#include "unity.h"

// setUp and tearDown are required, even if empty
void setUp(void) {}
void tearDown(void) {}

void test_reg_init_sets_default_values(void);


void test_vram_round_trip(void);
void test_echo_ram_mirrors_wram(void);
void test_rom_stub_reads_zero(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_reg_init_sets_default_values);


    RUN_TEST(test_vram_round_trip);
    RUN_TEST(test_echo_ram_mirrors_wram);
    RUN_TEST(test_rom_stub_reads_zero);

    return UNITY_END();
}

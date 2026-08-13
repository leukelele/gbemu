#include "unity.h"
#include "mmu.h"

void test_vram_round_trip(void) {
    bus_t bus = {0};
    bus_write8(&bus, 0x8000, 0x42);     // first byte of VRAM
    TEST_ASSERT_EQUAL_UINT8(0x42, bus_read8(&bus, 0x8000));

    bus_write8(&bus, 0x9FFF, 0x99);     // last byte of VRAM
    TEST_ASSERT_EQUAL_UINT8(0x99, bus_read8(&bus, 0x9FFF));
}

void test_echo_ram_mirrors_wram(void) {
    bus_t bus = {0};
    bus_write8(&bus, 0xC005, 0xAB);     // write through WRAM
    TEST_ASSERT_EQUAL_UINT8(0xAB, bus_read8(&bus, 0xE005)); // read echo

    bus_write8(&bus, 0xE010, 0xCD);
    TEST_ASSERT_EQUAL_UINT8(0xCD, bus_read8(&bus, 0xC010));
}

void test_rom_stub_reads_zero(void) {
    bus_t bus = {0};
    TEST_ASSERT_EQUAL_UINT8(0x00, bus_read8(&bus, 0x0000));
    TEST_ASSERT_EQUAL_UINT8(0x00, bus_read8(&bus, 0x7FFF));
}

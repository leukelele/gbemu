#include "mmu.h"
#include <stdint.h>

uint8_t bus_read8(bus_t *bus, uint16_t addr) {
    if (addr <= 0x7FFF) return 0x00; // cart ROM, though stubbed due to no
                                     // cartridge loader yet
    else if (addr <= 0x9FFF) return bus->vram[addr - 0x8000];

    return 0x00;
}

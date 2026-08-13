#include "mmu.h"
#include <stdint.h>

uint8_t bus_read8(bus_t *bus, uint16_t addr) {
    // In order as the following statements:
    // - cartridge ROM, though it is currently a stub as there is no cartridge
    //   loader yet
    // - video RAM is where the PPU (graphics chip) will use
    // - external memory, I haven't a clue what this is for
    //   work RAM, for general purpose
    // - echo RAM, which is suppose to mirror work RAM though idk its purpose
    // - object attribute memory is where the sprites will be stored
    // - not usable memory? as Nintendo has stated
    // - I/O registers
    // - high RAM
    // - interrupt enable register
    if (addr <= 0x7FFF) return 0x00;
    else if (addr <= 0x9FFF) return bus->vram[addr - 0x8000];
    else if (addr <= 0xBFFF) return 0x00;
    else if (addr <= 0xDFFF) return bus->wram[addr - 0xC000];
    else if (addr <= 0xFDFF) return bus->wram[addr - 0xE000];
    else if (addr <= 0xFE9F) return bus->oam[addr - 0xFE00];
    else if (addr <= 0xFEFF) return 0x00;
    else if (addr <= 0xFF7F) return bus->io[addr - 0xFF00];
    else if (addr <= 0xFFFE) return bus->hram[addr - 0xFF80];
    else if (addr == 0xFFFF) return bus->ie;

    return 0x00;
}   // bus_read8()

void bus_write8(bus_t *bus, uint16_t addr, uint8_t value) {
    if (addr <= 0x7FFF) return;
    else if (addr <= 0x9FFF) bus->vram[addr - 0x8000] = value;
    else if (addr <= 0xBFFF) return;
    else if (addr <= 0xDFFF) bus->wram[addr - 0xC000] = value;
    else if (addr <= 0xFDFF) bus->wram[addr - 0xE000] = value;
    else if (addr <= 0xFE9F) bus->oam[addr - 0xFE00]  = value;
    else if (addr <= 0xFEFF) return;
    else if (addr <= 0xFF7F) bus->io[addr - 0xFF00]   = value;
    else if (addr <= 0xFFFE) bus->hram[addr - 0xFF80] = value;
    else if (addr == 0xFFFF) bus->ie                  = value;
}   // bus_write8()

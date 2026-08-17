#include <stdint.h>
#include "mmu.h"

uint8_t bus_read8(struct bus *bus, uint16_t addr) {
    if (addr <= 0x7FFF) return 0x00;        // cartridge ROM that is WIP
    else if (addr <= 0x9FFF) return bus->vram[addr - 0x8000];
    else if (addr <= 0xBFFF) return 0x00;   // same reason for WIP
    else if (addr <= 0xDFFF) return bus->wram[addr - 0xC000];
    else if (addr <= 0xFDFF) return bus->wram[addr - 0xE000];
    else if (addr <= 0xFE9F) return bus->oam [addr - 0xFE00];
    else if (addr <= 0xFEFF) return 0x00;   // region in mem that is unusable
    else if (addr <= 0xFF7F) return bus->io  [addr - 0xFF00];
    else if (addr <= 0xFFFE) return bus->hram[addr - 0xFF80];
    else if (addr == 0xFFFF) return bus->ie;

    return 0x0;
}   // bus_read8()

uint16_t bus_read16(struct bus *bus, uint16_t addr) {
    uint8_t lo = bus_read8(bus, addr);
    uint8_t hi = bus_read8(bus, addr + 1);
    return (uint16_t)(hi << 8) | lo;
}   // bus_read16()

void bus_write8(struct bus *bus, uint16_t addr, uint8_t value) {
    if (addr <= 0x7FFF) return;
    else if (addr <= 0x9FFF) bus->vram[addr - 0x8000] = value;
    else if (addr <= 0xBFFF) return;
    else if (addr <= 0xDFFF) bus->wram[addr - 0xC000] = value;
    else if (addr <= 0xFDFF) bus->wram[addr - 0xE000] = value;
    else if (addr <= 0xFE9F) bus->oam [addr - 0xFE00] = value;
    else if (addr <= 0xFEFF) return;    // attempts at use should return
    else if (addr <= 0xFF7F) bus->io  [addr - 0xFF00] = value;
    else if (addr <= 0xFFFE) bus->hram[addr - 0xFF80] = value;
    else if (addr == 0xFFFF) bus->ie                  = value;
}   // bus_write8()

void bus_write16(struct bus *bus, uint16_t addr, uint16_t value) {
    bus_write8(bus, addr, value & 0xff);
    bus_write8(bus, addr + 1, (value >> 8) & 0xFF);
}   //bus_write16()

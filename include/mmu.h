/**
 * Defines the memory bus interface used by the DMG-CPU and system components.
 *
 * This header file provides the declarations for the emulator's memory bus,
 * which acts as the central access layer for all memory operations. Instead of
 * accessing memory regions directly, system components interact with memory
 * through the bus interface.
 *
 * It declares functions such as:
 * - `bus_read8`, which reads a byte from a specified address
 * - `bus_write8`, which writes a byte to a specified address
 *
 * This abstraction ensures that the CPU implementation remains independent
 * of the underlying memory layout and hardware mappings.
 */
#ifndef MMU_H
#define MMU_H

#include <stdint.h>

// cartridge isn't built yet. Forward-declare it so bus.h doesn't need to
// know its internals, just that it exists.
typedef struct cartridge cartridge_t;

typedef struct {
    uint8_t vram[0x2000];  // 8000h-9FFFh video RAM, PPU's area of memory
    uint8_t wram[0x2000];  // C000h-DFFFh general memory
    uint8_t oam[0xA0];     // FE00h-FE9Fh table for sprites
    uint8_t io[0x80];      // FF00h-FF7Fh placeholder until real regs exist
    uint8_t hram[0x7F];    // FF80h-FFFEh general, but more for time-sensitive
    uint8_t ie;            // FFFFh

    cartridge_t *cart; // 0000h-7FFFh and A000h-BFFFh forward here
} bus_t;

uint8_t bus_read8 (bus_t *bus, uint16_t addr);
void    bus_write8(bus_t *bus, uint16_t addr, uint8_t value);

#endif

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
#ifndef BUS_H
#define BUS_H

#include <stdint.h>

/**
 * The cartridge has not yet been built WIP. For now, it will be forward-
 * declared so that mmu.h is atleast aware that it exists.
 */
struct cartridge;

/**
 * Each field maps to a fixed hardware address range as to mimic the memory map
 * found in the pandoc (though, I have also stored it in gbemu/docs/). There
 * are also special areas in memory such as: 
 *  - echo RAM, which mirrors 0xC000-0xDDFF in working RAM, and 
 *  - 0xFEA0-0xFEFF, which is unusable RAM.
 */
struct bus {
    uint8_t vram[0x2000];   // 0x8000-0x9FFF video RAM, PPU's area of memory
    uint8_t wram[0x2000];   // 0xC000-0xDFFF general memory
    uint8_t oam [0xA0];     // 0xFE00-0xFE9F table for sprites
    uint8_t io  [0x80];     // 0xFF00-0xFF7F placeholder until real regs exist
    uint8_t hram[0x7F];     // 0xFF80-0xFFFE general mem but for time-sensitive
    uint8_t ie;             // 0xFFFF interrupt enabel register

    struct cartridge *cart; // 0x0000-0x7FFF and 0xA000h-0xBFFF forward here
};

/**
 * The function, when given parameters, returns the byte stored in the
 * particular location in memory.
 * 
 * @param[in] bus The bus instance that is to be read by the function.
 * @param[in] addr The 16-bit bit address to be read by the function in
 *                 correlation with the bus.
 * @return The byte stored in the memory region (represented by `bus`) for 
 *         `addr`.
 */
uint8_t bus_read8 (struct bus *bus, uint16_t addr);

/**
 * The function, when given parameters, returns the byte stored in the
 * particular location in memory. Because it is a request for 16 bits, the
 * function effictively calls `bus_read8()` twice.
 * 
 * @param[in] bus The bus instance that is to be read by the function.
 * @param[in] addr The 16-bit bit address to be read by the function in
 *                 correlation with the bus.
 * @return The byte stored in the memory region (represented by `bus`) for 
 *         `addr`.
 */
uint16_t bus_read16(struct bus *bus, uint16_t addr);

/**
 * The function, when given parameters, writes to the memory location.
 * 
 * @param[in, out] bus The bus instance that is to be read and modified.
 * @param[in] addr The 16-bit bit address.
 * @param[in] value The byte to store in the memory region assoicated
 *                  with `addr`
 */
void bus_write8(struct bus *bus, uint16_t addr, uint8_t value);

/**
 * The function, when given parameters, writes to the memory location. It
 * essnetially calls `bus_write8()` twice.
 * 
 * @param[in, out] bus The bus instance that is to be read and modified.
 * @param[in] addr The 16-bit bit address.
 * @param[in] value The byte to store in the memory region assoicated
 *                  with `addr`
 */
void bus_write16(struct bus *bus, uint16_t addr, uint16_t value);

#endif

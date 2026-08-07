/**
 * The gameboy actually does not have a physically separate mmu unit and the
 * CPU itself is responsibile for memory management; this is really just a
 * software abstraction.
 */

#include <stdint.h>

typedef struct {
    uint8_t memory[0x10000];
//    uint8_t wram[0x2000];      // 8 KB working RAM
//    uint8_t vram[0x2000];      // 8 KB video RAM
//    uint8_t hram[0x007F];      // 127 B high RAM
//    uint8_t oam[0x00A0];       // sprite attribute memory
//    uint8_t io_regs[0x0080];   // I/O registers
//    uint8_t ie;                // interrupt enable (0xFFFF)
//    // plus pointers/structures for:
//    //   cartridge ROM
//    //   external RAM (cartridge)
//    //   bank switching state
} mmu_t;

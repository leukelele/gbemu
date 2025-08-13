#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

/** 
 * The registers of the DMG-CPU are paired to form 16 bit registers; this
 * design allows for both 8-bit and 16-bit operations using the same set of
 * registers. Further elaboration may be found in the documentation.
 */
typedef union {
    struct {
        uint8_t lo;
        uint8_t hi;
    } bytes;
    uint16_t reg;
} reg_pair_t;

/** 
 * The DMG-CPU registers are typically paired as follows (in addition to the
 * stack pointer and program counter):
 */
typedef struct {
    reg_pair_t af;  // accumulator and flag
    reg_pair_t bc;  // general purpose reg
    reg_pair_t de;  // general purpose reg
    reg_pair_t hl;  // general purpose reg; mainly for memory addressing
    uint16_t   sp;  // stack pointer
    uint16_t   pc;  // program counter
} cpu_regs_t;

#endif

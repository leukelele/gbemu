/**
 * Helpers for reading and writing the DMG-CPU's flag register (F, the low
 * byte of AF). Only the upper nibble of F is physically wired on real
 * hardware (Z, N, H, C). Every instruction that touches flags should do so
 * exclusively through helpers so that invariant holds without each call site
 * having to think about it.
 */
#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>
#include <stdint.h>

#define FLAG_Z 0x80 // zero flag: set when the result of an op is 0
#define FLAG_N 0x40 // subtract flag: set after a subtraction-based op
#define FLAG_H 0x20 // half-carry flag: carry/borrow out of bit 3
#define FLAG_C 0x10 // carry flag: carry/borrow out of bit 7 (or bit 15)

struct cpu; // forward declaration, defined in cpu.h

/**
 * sets or clears the bit(s) in `mask` within the F register depending on
 * `condition`. Multiple flag bits may be combined in `mask` to set/clear
 * them together
 *
 * @param[in,out] cpu The CPU whose F register is to be modified.
 * @param[in] mask One or more of the FLAG_* bit masks.
 * @param[in] condition If true, the masked bits are set; if false, cleared.
 */
void flag_set(struct cpu *cpu, uint8_t mask, bool condition);

/**
 * Reads whether the given flag bit(s) are currently set.
 *
 * @param[in] cpu The CPU whose F register is to be read.
 * @param[in] mask One or more of the FLAG_* bit masks.
 * @return true if all bits in `mask` are set in F, false otherwise.
 */
bool flag_get(const struct cpu *cpu, uint8_t mask);

#endif

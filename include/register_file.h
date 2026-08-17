/**
 * Defines the register structures and initialization function for the DMG-CPU.
 *
 * This header file provides the definitions for: 
 * - the 8-bit register pairs (`reg_pair`) and 
 * - the full register file (`reg_file`) used in the DMG-CPU architecture. It 
 *   also declares
 * - the `reg_init` function, which initializes the register file to its 
 *   default values.
 *
 * @note Further documentation on the DMG-CPU architecture and register usage
 * can be found in the project documentation.
 */
#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <stdint.h>

/** 
 * The registers of the DMG-CPU are paired to form 16 bit registers; this
 * design allows for both 8-bit and 16-bit operations using the same set of
 * registers.
 */
union reg_pair{
    struct {
        uint8_t lo;
        uint8_t hi;
    } byte;
    uint16_t pair;
};

/** 
 * The DMG-CPU register file is formulated by the registers paired as follows
 * (in addition to the stack pointer and program counter):
 */
struct reg_file {
    union reg_pair af;  // accumulator and flag
    union reg_pair bc;  // general purpose reg
    union reg_pair de;  // general purpose reg
    union reg_pair hl;  // general purpose reg; mainly for memory addressing
    uint16_t       sp;  // stack pointer
    uint16_t       pc;  // program counter
};

/**
 * The function sets all registers in the `reg_file` structure to their
 * predefined default values, preparing the CPU for operation.
 *
 * @param[out] reg_file Pointer to the `reg_file` structure to be initialized.
 *                      The structure's fields will be set to default values.
 *
 * @note The reason for taking a pointer is for passing through structures.
 *       Additionally this would allow multiple functions to modify the same
 *       register file instance.
 */
void reg_init(struct reg_file *reg_file);

#endif

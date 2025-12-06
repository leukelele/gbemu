#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

/**
 * Instruction formats supported by the DMG-CPU. WIP and subject to change.
 */
typedef enum {
    // load operations
    LD,   // loads 8-/16-bit data between registers/memory
    LDH,  // loads from High RAM, access ranges from 0xFF00 - 0xFFFF
    PUSH, // push onto the stack
    POP,  // pop from the stack

    // arithmetic
    ADD,  // adds the source value to the accumulator (register A)
    ADC,  // adds a value and carry flag to A
    SUB,  // subtracts a value from A
    SBC,  // subtracts a value plus carry flag from A
    CP,   // compares val w A by subtracting (without storing)
    INC,  // increments a register or memory location by 1
    DEC,  // decrements a register or memory location by 1
    AND,  // performs bitwise AND with A
    OR,   // bitwise OR w A
    XOR,  // bitwise XOR w A
    CCF,  // complements the carry flag
    SCF,  // sets the carry flag
    DAA,
    CPL,  // complements the accumulator

    // rotate, shift, and bit operations
    RLCA, // rotates A left in a circular manner
    RRCA, // rotates A right in a circular manner
    RLA,  // rotates A left through carry
    RRA,  // rotates A right through carry
    RLC,  // rotates any 8-bit register left
    RRC,  // rotates any 8-bit register right
    RL,   // rotates value left through carry
    RR,   // rotates value right through carry
    SLA,  // arithmetic shift left
    SRA,  // arithmetic shift right
    SWAP, // swaps upper and lower nibbles (4-bit halves) of a register/memory
    SRL,  // logical shift right
    BIT,  // tests a bit in a register or memory
    RES,  // resets (clears) a specified bit in a register or memory
    SET,  // sets a specified bit in a register or memory

    // control flow
    JP,   // jumps to a specified address
    JR,   // jumps to a relative address offset
    CALL, // calls a subroutine by pushing PC and jumping to the address
    RET,  // returns from a subroutine by popping PC from the stack.
    RETI, // returns from a subroutine and enables interrupts
    RST,  // restarts via a fixed (hard-coded) address, like a fast-call

    // misc.
    HALT, // halts the CPU until an interrupt occurs (low-power standby)
    STOP, // stops the CPU
    DI,   // disables interrupts
    EI,   // enables interrupts
    NOP,  // does nothing (no operation), used to consume one cycle
} inst_fmt;

/**
 * The complete structure of the instructions. TODO:
 * - opcode byte
 * - cycle
 * - size metadata?
 * - execute function (probably?)
 */
typedef struct {
    inst_fmt format;
} instruction;

#endif

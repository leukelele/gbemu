#ifndef REGISTER_H
#define REGISTER_H

#include <common.h>

// simulation of register pairings
typedef union {
	struct {
		u8 lo;
		u8 hi;
	};
	u16 reg;
} register_pair;

// cpu registers
typedef struct {
	register_pair af;  // accumulator and flag
	register_pair bc;  // general purpose reg
	register_pair de;  // general purpose reg
	register_pair hl;  // general purpose reg; mainly for memory addressing
	u16 sp;            // stack pointer
	u16 pc;            // program counter
} cpu_registers;

#endif

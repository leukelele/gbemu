#ifndef CPU_H
#define CPU_H

#include <common.h>

// simulation of register pairings
typedef union {
	struct {
		u8 lo;
		u8 hi;
	};
	u16 reg;
} reg_pair;

typedef struct {
	reg_pair af;  // accumulator and flag
	reg_pair bc;  // general purpose reg
	reg_pair de;  // general purpose reg
	reg_pair hl;  // general purpose reg; mainly for memory addressing
	u16 sp;       // stack pointer
	u16 pc;       // program counter
} cpu_registers;

#endif

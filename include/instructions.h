#ifndef ISA_H
#define ISA_H

#include <common.h>
#include <register.h>

typedef enum {
	// load
	LD,
	LDH,
	PUSH,
	POP,

	// arithmetic
	ADD,
	ADC,
	SUB,
	SBC,
	CP,
	INC,
	DEC,
	AND,
	OR,
	XOR,
	CCF,
	SCF,
	DAA,
	CPL,

	// rotate, shift, and bit operations
	RCLA,
	RRCA,
	RLA,
	RRA,
	RLC,
	RRC,
	RL,
	RR,
	SLA,
	SRA,
	SWAP,
	SRL,
	BIT,
	RES,
	SET,

	// control flow
	JP,
	JR,
	CALL,
	RET,
	RETI,
	RST,

	// misc.
	HALT,
	STOP,
	DI,
	EI,
	NOP,
} instruction;

typedef enum {
} addr_mode;

#endif

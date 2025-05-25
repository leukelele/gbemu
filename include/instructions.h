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
	IMP,
	R_D16,
	R_R,
	MR_R,
	R,
	R_D8,
	R_MR,
	R_HLI,
	R_HLD,
	HLI_R,
	HLD_R,
	R_A8,
	A8_R,
	HL_SPR,
	D16,
	D8,
	D16_R,
	MR_D8,
	MR,
	A16_R,
	R_A16
} addr_mode;

#endif

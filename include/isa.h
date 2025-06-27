#ifndef ISA_H
#define ISA_H

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
} inst_type;

typedef enum {
	// register
	REG,
	REG16,

	// immediate values
	IMM8,
	IMM16,

	// direct memory addressed by immediate
	ADDR16,

	// high-page immediate
	HIGH_IMM8,

	// register-indirect addressing
	MEM_BC,
	MEM_DE,
	MEM_HL,

	// (HL+) and (HL–) auto-increment/decrement forms
	MEM_HL_INC,
	MEM_HL_DEC,

	// stack pointer / register pair operations
	SP_REL,

	// lelative immediate jumps
	REL8,

	// conditional
	BITWISE,
	RES_SET,
	ROT_SHIFT,
} addr_mode;

typedef struct {
	inst_type type ;
} instruction;

#endif

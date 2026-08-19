#include <stdio.h>
#include "register_file.h"

void reg_init(struct reg_file *reg_file) {
    // init registers according to the original bootstrap rom
    reg_file->af.pair = 0x01B0;
    reg_file->bc.pair = 0x0013;
    reg_file->de.pair = 0x00D8;
    reg_file->hl.pair = 0x014D;
    reg_file->sp      = 0xFFFE;
    reg_file->pc      = 0x0100;

    // console logging
    fprintf(stdout, "Initialized registers: ");
    fprintf(stdout, "AF=0x%04X, BC=0x%04X, DE=0x%04X, HL=0x%04X, SP=0x%04X,",
            reg_file->af.pair, reg_file->bc.pair, reg_file->de.pair,
            reg_file->hl.pair, reg_file->sp);
    fprintf(stdout, " PC=0x%04X\n", reg_file->pc);
}

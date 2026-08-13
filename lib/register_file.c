#include <stdio.h>
#include "register_file.h"

void reg_init(struct reg_file *reg_file) {
    // init registers according to the original bootstrap rom
    reg_file->af.reg = 0x01B0;
    reg_file->bc.reg = 0x0013;
    reg_file->de.reg = 0x00D8;
    reg_file->hl.reg = 0x014D;
    reg_file->sp     = 0xFFFE;
    reg_file->pc     = 0x0100;

    // console logging
    fprintf(stdout, "Initialized registers: ");
    fprintf(stdout, "AF=0x%04X, BC=0x%04X, DE=0x%04X, HL=0x%04X, SP=0x%04X,",
            reg_file->af.reg, reg_file->bc.reg, reg_file->de.reg,
            reg_file->hl.reg, reg_file->sp);
    fprintf(stdout, " PC=0x%04X\n", reg_file->pc);
}

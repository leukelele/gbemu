#include "register_file.h"

void reg_init(reg_file *reg_file) {
    // init registers according to the original bootstrap rom
    reg_file->af.reg = 0x01B0;
    reg_file->bc.reg = 0x0013;
    reg_file->de.reg = 0x00D8;
    reg_file->hl.reg = 0x014D;
    reg_file->sp     = 0xFFFE;
    reg_file->pc     = 0x0100;
}

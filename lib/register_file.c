#include "register_file.h"

void reg_init(reg_file *reg_file) {
    // init registers according to the original bootstrap rom
    reg_file->af.reg = 0x01b0;
    reg_file->bc.reg = 0x0013;
    reg_file->de.reg = 0x00d8;
    reg_file->hl.reg = 0x014d;
    reg_file->sp     = 0xfffe;
    reg_file->pc     = 0x0100;
}

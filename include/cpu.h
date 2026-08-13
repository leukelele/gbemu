#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "register_file.h"
#include "mmu.h"

struct cpu {
    struct reg_file regs;
    struct bus *bus;
};

void    cpu_init(void);
uint8_t fetch(void);

#endif

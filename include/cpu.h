/**
 * The file concerns with the CPU loop of fetch -> decode -> execute. The CPU,
 * as is in the real world, will be the main driver of the system. It will
 * allow for the gameboy to function as would a gameboy.k
 *
 * The header file defines the following:
 * - CPU struct `cpu` that will contains features typical to the DMG-CPU but
 *   also what it interacts with.
 * - `cpu_init` initializes the values of the `cpu`
 * - `fetch`
 * - `decode`
 * - `execute`
 */
#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "register_file.h"
#include "mmu.h"

struct cpu {
    struct reg_file regs;
    struct bus *bus;
};

void    cpu_init(struct cpu *cpu, struct bus *bus);
uint8_t fetch(struct cpu *cpu);
uint8_t decode(void);
uint8_t execute(void);

#endif

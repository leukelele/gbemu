/**
 * The file concerns with the CPU loop of fetch -> decode -> execute. The CPU,
 * as is in the real world, will be the main driver of the system. It will
 * allow for the gameboy to function as would a gameboy.
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
#include "instruction_set.h"

/**
 * TThis struct is especially subject to changes through the course of this
 * project. Regardless, this struct contains all variables required for the
 * CPU to appropriately complete a fetch->decode->execute loop. Currently,
 * this is just the registers and the bus that the CPU interacts with.
 */
struct cpu {
    struct reg_file regs;
    struct bus *bus;
};

/**
 * The function initializes the CPU registers and connects it to the bus.
 * 
 * @param[in] cpu The registers are initialized by reg_init
 * @param[in] bus The bus instance that is to be read by the function.
 *                 correlation with the bus.
 */
void cpu_init(struct cpu *cpu, struct bus *bus);

/**
 * Bundles the complete CPU loop: fetch -> decode -> execute.
 *
 * @param[in] cpu This is for the CPU's registers
 *
 * @return The machine cycles as this is the only way to know how long the
 *         instruction will execute.
 */
uint8_t cpu_step(struct cpu *cpu);

#endif

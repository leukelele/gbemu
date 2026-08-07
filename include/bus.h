/**
 * Defines the memory bus interface used by the DMG-CPU and system components.
 *
 * This header file provides the declarations for the emulator's memory bus,
 * which acts as the central access layer for all memory operations. Instead of
 * accessing memory regions directly, system components interact with memory
 * through the bus interface.
 *
 * It declares functions such as:
 * - `bus_read8`, which reads a byte from a specified address
 * - `bus_write8`, which writes a byte to a specified address
 *
 * This abstraction ensures that the CPU implementation remains independent
 * of the underlying memory layout and hardware mappings.
 */
#ifndef BUS_H
#define BUS_H


#endif

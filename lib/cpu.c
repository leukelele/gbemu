#include "cpu.h"
#include "register_file.h"
#include <stdio.h>

void cpu_init(void) {
    // declare a CPU register file instance and initialize it
    // this ensures the pointer refers to valid memory before initialization
    struct reg_file cpu_instance;
    struct reg_file *dmg_cpu = &cpu_instance;

    reg_init(dmg_cpu);  // intiialize DMG01 to initialized values

    printf("hello world!\n");
}

uint8_t fetch(void) {
    return 0;
}

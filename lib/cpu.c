#include "cpu.h"
#include "register_file.h"
#include <stdio.h>

void cpu_init(void) {
    // Declare a CPU register file instance and initialize it.
    // This ensures the pointer refers to valid memory before initialization.
    reg_file cpu_instance;
    reg_file *dmg_cpu = &cpu_instance;
    reg_init(dmg_cpu);

    printf("hello wordl!\n");
}

uint8_t fetch(void) {
    return 0;
}

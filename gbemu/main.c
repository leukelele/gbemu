#include "cpu.h"

int main(int argc, char **argv) {
    struct bus bus = {0};
    struct cpu cpu;
    cpu_init(&cpu, &bus);
    return 0;
}

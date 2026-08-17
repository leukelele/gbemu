#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#define STACK_CAPACITY 0xFFFE

struct stack {
    uint16_t data[STACK_CAPACITY];
    uint16_t top;
};

#endif

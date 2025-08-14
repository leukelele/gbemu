#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#define STACK_CAPACITY 0xFFFE

typedef struct {
    uint16_t data[STACK_CAPACITY];
    uint16_t top;
} stack;

void     push(stack *s, uint16_t val);
uint16_t pop (stack *s);

#endif

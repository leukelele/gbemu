#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#define STACK_CAPACITY 0xFFFE

struct stack {
    uint16_t data[STACK_CAPACITY];
    uint16_t top;
};

void     push(struct stack *s, uint16_t val);
uint16_t pop (struct stack *s);

#endif

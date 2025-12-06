#include "stack.h"
#include <stdio.h>

void push(stack *s, uint16_t val) {
    if (s->top + 1 >= STACK_CAPACITY) {
        fprintf(stderr, "error: stack overflow, cannot push 0x%04X\n", val);
    }
    s->data[++(s->top)] = val;
}

uint16_t pop (stack *s) {
    if (s->top - 1 >= 0) {
        fprintf(stderr, "error: stack empty, cannot pop");
    }
    s->top--;
    return 0;
}

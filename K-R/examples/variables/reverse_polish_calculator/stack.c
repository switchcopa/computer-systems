#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define STACK_SIZE 100

double stack[STACK_SIZE];
int sp = -1;

double pop(void) {
        if (sp >= 0) 
                return stack[sp--];
        else {
                fprintf(stderr, "error: pop from empty stack\n");
                exit(EXIT_FAILURE);        
        }
}

void push(double d) {
        if (sp < STACK_SIZE)
                stack[++sp] = d;
        else 
                fprintf(stderr, "error: push from full stack\n");
}

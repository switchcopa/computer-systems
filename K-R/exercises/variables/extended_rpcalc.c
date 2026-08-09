#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define BUF_SIZE 2048
#define STACK_SIZE 1028

double pop(void);
void push(double);
double peek(void);
void swaptop(void);

char *operation = "5 6 2 + * 12 4 / -";
int op_ptr;
double stack[STACK_SIZE]; 
int sp = -1;

int main(void) {
        int c;

        for (op_ptr = 0; (c = operation[op_ptr]) != '\0'; op_ptr++) {
                if (isdigit(c) || (c == '-' && isdigit(operation[op_ptr + 1]))) {
                        char *end;
                        double val = strtod(&operation[op_ptr], &end);
                        push(val);
                        op_ptr = end - operation - 1;
                }
        
                else if (c == '-') {
                        double op2 = pop();
                        push(pop() - op2); 
                }

                else if (c == '+') 
                        push(pop() + pop()); 

                else if (c == '/') {
                        double op2 = pop();
                        if (op2 == 0.0) {
                                perror("error: division by zero\n");
                                exit(EXIT_FAILURE);
                        }
                        
                        push(pop() / op2);
                }

                else if (c == '*') 
                        push(pop() * pop());
                
                else if (c == '%') 
                        push(pop() % pop());

                else if (c == ' ') 
                        continue;

                else fprintf(stderr, "Unknown token %c\n", c);
        }
        
        printf("result: %.8f\n", pop());
        return 0;
}

double pop(void) {
        if (sp >= 0)
                return stack[sp--];
        else {
                perror("error: pop empty stack\n");
                return 0.0;
        }
}

void push(double d) {
        if (sp < STACK_SIZE - 1) 
                stack[++sp] = d;
        else 
                perror("error: push from full stack\n");
}

double peek(void) {
        if (sp >= 0)
                return stack[sp];
        else {
                perror("error: peek empty stack\n");
                return 0.0;
        }
}

void swaptop(void) {
        if (sp >= 1) { 
                double temp = stack[sp];
                stack[sp] = stack[sp - 1];
                stack[sp - 1] = temp;
        } else 
                perror("error: cannot swap two top elements\n");
}

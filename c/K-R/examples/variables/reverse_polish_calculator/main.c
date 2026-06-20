#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calc.h"

#define BUF_SIZE 100

static char buf[BUF_SIZE]; 
static int bufp;

int main() {
        int c;

        while (get_line(buf, BUF_SIZE) > 0) {
                printf("input: %s\n", buf);

                for (bufp = 0; (c = buf[bufp]) != '\0'; bufp++) {
                        if (isdigit(c) || (c == '-' && isdigit(buf[bufp + 1]))) {
                                char *end;
                                double val = strtod(&buf[bufp], &end);
                                push(val);
                                bufp = end - buf - 1;
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

                        else if (c == ' ') 
                                continue;

                        else fprintf(stderr, "Unknown token %c\n", c);
                }
                
                printf("result: %.8f\n", pop());
        }

        return 0;
}

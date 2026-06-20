
/*  
 *  expr: Program that evaluates a reverse Polish expression from the
 *  command line
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define STACK_SIZE 128
double stack[STACK_SIZE];
int sp = -1;

double pop(void);
void push(double);
bool is_operator(char);

int
main(int argc, char **argv)
{
	char c;
	char *p;
	double num;

	if (argc < 4)
	{
		printf("Usage example: ./expr 2 3 *\n");
		return 1;
	} 
	
	while (--argc > 0 && (p = *++argv) != NULL)
	{
		c = *p;
		if (isdigit(*p))
			push(atof(p));
		else if (is_operator(c))
			switch (c) 
			{
				case '-':
					num = pop();
					push(pop() - num);
					break;
				case '+':
					push(pop() + pop());
					break;
				case '*':
					push(pop() * pop());
					break;
				case '/':
					num = pop();
					if (num == 0.0)
					{
						perror("zero division error\n");
						exit(EXIT_FAILURE);
					}

					push(pop() / num);
					break;
				default:
					printf("Unknown operator '%c'\n", c);
					exit(EXIT_FAILURE);
					break;
			}
		else
		{
			printf("Unknown operator '%c'\n", c);
			exit(EXIT_FAILURE);
		}
	}

	if (sp == 0) 
        {
		printf("%.5f\n", pop());
		return 0;
        }        
	else 
        {
		perror("Stack still full\n");
		return -1;
        }
}

double
pop(void)
{
        if (sp >= 0)
                return stack[sp--];
        else 
	{
		perror("pop from empty stack\n");	
		exit(EXIT_FAILURE);
	}
}

void
push(double d) {
        if (sp < STACK_SIZE - 1)
                stack[++sp] = d;
        else 
        {
		perror("push from full stack\n");
		exit(EXIT_FAILURE);
	}
}

bool
is_operator(char c)
{
	return (c == '-') || (c == '+') || (c == '/') || (c == '*');
}

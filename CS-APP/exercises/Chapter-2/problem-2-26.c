/*
You are given the assignment of writing a function that determines whether one
string is longer than another. You decide to make use of the string library function
strlen having the following declaration:

// Prototype for lib function strlen
size_t strlen(const char *s);

Here is your first attempt at the function:

// Determine whether string s is longer than string t
// Warning: this function is buggy

int strlonger(char *s, char *t)
{
    return strlen(s) - strlen(t) > 0;
}

When you test this on some sample data, things do not seem to work quite
right. You investigate further and determine that, when compiled as a 32-bitprogram, data type size_t is defined (via typedef) in header file stdio.h to be
unsigned.

A. For what cases will this function produce an incorrect result?
B. Explain how this incorrect result comes about.
C. Show how to fix the code so that it will work reliably.
*/

/*
Solution:
A. When strlen(s) < strlen(t)
B. If we have strlen(s) < strlen(t), the result strlen(s) - strlen(t) will be mathematically
negative, but since size_t is defined to be unsigned by the standard, their differences 
will be casted to an unsigned integer, and so strlen(s) - strlen(t) > 0 will be true, 
even though it is not.
C. Simply check strlen(s) > strlen(t):
*/

#include "string.h"

int strlonger(char *s, char *t)
{
    return strlen(s) > strlen(t);
}

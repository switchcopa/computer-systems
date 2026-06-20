
/* A union in C is a user-defined type similar to a struct, but all members share the same memory location.
This means a union can store one value at a time, but that value can be of different types. */

union example {
    int i;
    float f;
    char c;
};

/* sizeof(union example) == sizeof(the largest element of the union) */ 
/* All members start at the same memory address */

union example v;
v.i = 10;
v.d = 3.14;

/* Here is a union inside a struct (Or tagged union) */


struct token {
    enum { INT, DOUBLE, CHAR } type;
    union {
        int i;
        double d;
        char c;
    } value;
};

struct token t;
t.type = INT;
t.value.i = 67;

if (t.type == INT)
    printf("%d\n", t.value.i);

/* References
ISO/IEC 9899:2018 (C17 standard), §6.7.2.1 “Structure and union specifiers”
K&R 2nd Edition, Chapter 6
*/

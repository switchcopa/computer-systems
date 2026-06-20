/* 
 * 5.1 - Pointers & Addresses
Let us begin with a simplified picture of how memory is organized. A typical machine has an
array of consecutively numbered or addressed memory cells that may be manipulated
individually or in contiguous groups. One common situation is that any byte can be a char, a
pair of one-byte cells can be treated as a short integer, and four adjacent bytes form a long. A
pointer is a group of cells (often two or four) that can hold an address. So if c is a char and p
is a pointer that points to it, we could represent the situation this way:

The unary operator & gives the address of an object, so the statement:
*/

int c = 5;
int *p = &c;

/*
assigns the address of c to the variable p, and p is said to ``point to'' c. The & operator only
applies to objects in memory: variables and array elements. It cannot be applied to expressions,
constants, or register variables.
The unary operator * is the indirection or dereferencing operator; when applied to a pointer, it
accesses the object the pointer points to. Suppose that x and y are integers and ip is a pointer
to int. This artificial sequence shows how to declare a pointer and how to use & and *:
*/

int x = 1;
int y = 2;
int z[10];

ip = &x; /* ip now points to x */
y = *ip; /* y is now 1 */
*ip = 0; /* x is now 0 */
ip = &z[0]; /* ip now points to z[0] */

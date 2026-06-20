# STYLE

This file defines the coding rules and conventions for this repository, which contains exercises
and programs based on **The C Programming Language** by K&R.
Following these rules ensures consistency, readability, and alignment with K&R style.

---

## 1. Function Definitions
- All functions must be defined like this:

```c
type function_name(arguments) {
    ...
}
```

. Example:

```c
int add_numbers(int a, int b) {
    return a + b;
}
```

## 2. Variables
- All variable names should be **snake_case**.
- Frequently used variables can be **global** or defined as a **macro**.
- Redundant variables should be replaced by **pointers** if possible.
- Avoid unnecessary temporary variables.

## 3. Macros

- Small functions should be written as **macro functions** when appropriate.

. Example:

```c

#define SQUARE(X) ((X)*(X))

```

## 4. Loops and Conditionals

All `if`, `for` and `while` statements should follow this K&R multi-line style:

```c
while (condition) {
    ...
}

for (init; condition; increment) {
    ...
}

if (condition) {
    ...
}
```

## 5. Files

Each program file should start with a **short descriptive comment** explaining its 
purpose.

. Example: 
```
/*
 * program_name.c
 * Description: This program calculates the factorial of a number.
 */
```

## 6. Compilation

All C files should be compiled with the following flags:

```bash
gcc -g -std=c11 filename.c -o output_name
```

if the file is a test or a debug program, the output can be named `test` or `debug`.

## 7. Optimization

- Use pointers instead of unnecessary temporary variables whenever it reduces memory usage or simplifies code:

```c
int x = 10;
int *ptr = &x;  // prefer this if x is frequently accessed
```
- Avoid redundant computations: store results of repeated calculations in a variable or macro if needed multiple times.

```c
#define PI 3.14159
double area = PI * radius * radius;  // instead of computing each time
```

- Use `const` where possible: helps compiler optimize and signals immutability:

```c
const int max_size = 100;
```
- Avoid unnecessary memory allocations: reuse buffers or structures when possible.

- Use inline functions (if macros are unsafe): for small functions that need type safety, inline can replace a macro:

```c
inline int max(int a, int b) {
    return a > b ? a : b;
}
```

- Use bitwise operations when appropriate for flags, masks, or powers of two.

```c
int is_even = (x & 1) == 0;
```

- Minimize deep copies of structs or arrays: pass pointers instead.
```c
void process_array(int *arr, int n);  // instead of copying entire array
```

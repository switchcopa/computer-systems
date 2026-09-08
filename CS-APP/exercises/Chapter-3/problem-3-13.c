
/*
Practice Problem 3.13 (solution page 366)
The C code
*/

typedef signed int data_t1;
typedef signed short data_t2;
typedef unsigned char data_t3;
typedef signed long data_t4_0;
typedef unsigned long data_t4_1;

#define COMPA <
#define COMPB >=
#define COMPC <=
#define COMPD !=

/*
shows a general comparison between arguments a and b, where data_t, the data
type of the arguments, is defined (via typedef) to be one of the integer data types
listed in Figure 3.1 and either signed or unsigned. The comparison COMP is defined
via #define.
Suppose a is in some portion of %rdi while b is in some portion of %rsi. For
each of the following instruction sequences, determine which data types data_t
and which comparisons COMP could cause the compiler to generate this code.
(There can be multiple correct answers; you should list them all.)
*/

/*
A.
    cmpl %esi, %edi
    setl %al
B.
    cmpw %si, %di
    setge %al
C.
    cmpb %sil, %dil
    setbe %al
D.
    cmpq %rsi, %rdi
    setne %a

Solution: Look at the function signatures below,
and you can check the validity of each typedef and
#define in the generated assembly file "problem-3-13.s"
You'll see the same generated assembly above.
*/

int comp_A(data_t1 a, data_t1 b) {
    return a COMPA b;
}

int comp_B(data_t2 a, data_t2 b) {
    return a COMPB b;
}

int comp_C(data_t3 a, data_t3 b) {
    return a COMPC b;
}

int comp_D_0(data_t4_0 a, data_t4_0 b) {
    return a COMPD b;
}

int comp_D_1(data_t4_1 a, data_t4_1 b) {
    return a COMPD b;
}

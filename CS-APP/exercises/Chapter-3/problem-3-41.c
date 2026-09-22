
/*
Practice Problem 3.41
Consider the following structure declaration:
*/

struct test {
    short *p;
    struct {
        short x;
        short y;
    } s;

    struct test *next;
};

/*
This declaration illustrates that one structure can be embedded within another,
just as arrays can be embedded within structures and arrays can be embedded
within arrays.
The following procedure (with some expressions omitted) operates on this
structure:
*/

void st_init(struct test *st) {
    st->p    = &st->s.y;
    st->next = st;
    st->s.y  = st->s.x;
}

/*
A. The offsets of the following fields are:

short *p [0 ... 7]
short x [8 9]
short y [10 11]
padding [12 ... 15]
struct test *next [16 ... 23]

B. The total bytes of the structure is 24 bytes.


C. The compiler generates the following assembly code for st_init:

st_init:
    movl 8(%rdi), %eax
    movl %eax, 10(%rdi)
    leaq 10(%rdi), %rax
    movq %rax, (%rdi)
    movq %rdi, 12(%rdi)
    ret

On the basis of this information, fill in the missing 
expressions in the code for st_init.
*/

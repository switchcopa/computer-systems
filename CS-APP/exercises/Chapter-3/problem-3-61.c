
/*
3.61 ◆◆
In Section 3.6.6, we examined the following code as a candidate for the use of
conditional data transfer:
*/

long cread(long *xp) {
    return (xp ? *xp : 0);
}

/*
We showed a trial implementation using a conditional move instruction but argued
that it was not valid, since it could attempt to read from a null address.
Write a C function cread_alt that has the same behavior as cread, except
that it can be compiled to use conditional data transfer. When compiled, the
generated code should use a conditional move instruction rather than one of the
jump instructions. */

long cread_alt(long *xp) {
    long zero = 0;
    long *ptr = (xp != NULL) ? xp : &zero;
    return *ptr;
}

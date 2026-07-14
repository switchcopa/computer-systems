
/* 
Your coworker gets impatient with your analysis of the overflow conditions for
two’s-complement addition and presents you with the following implementation
of tadd_ok:

int tadd_ok(int x, int y) {
    int sum = x+y;
    return (sum-x == y) && (sum-y == x);
}

You look at the code and laugh. Explain why.
*/


/*
My coworker definitely doesn't know what two's complement arithmetic overflow is.
The problem is their whole function. It is mathematically logical, but legally
broken.
The thing is, by the time they did:

    int sum = x+y;

they violated the ISO C standard. The C standard explicitly mentions that two's
complement overflow is undefined behavior.
This is due to C's philosophy, as it is supposed to work on all architectures.
Some architectures still use one's complement or sign magnitude instead of
the standard two's complement, and it behaves differently, of course.
*/

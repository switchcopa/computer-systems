
/*
3.68 ◆◆◆
In the following code, A and B are constants defined with #define:
*/

typedef struct {
    int x[A][B]; /* Unknown constants A and B */
    long y;
} str1;

typedef struct {
    char array[B];
    int t;
    short s[A];
    long u;
} str2;

void setVal(str1 *p, str2 *q) {
    long v1 = q->t;
    long v2 = q->u;
    p->y = v1+v2;
}

/*
Gcc generates the following code for setVal: 

setVal:
    movslq 8(%rsi), %rax
    addq 32(%rsi), %rax
    movq %rax, 184(%rdi)
    ret

What are the values of A and B? (The solution is unique.)
*/

/*
 * So first of all from what I'm seeing here is that the way
 * we access p->y, we have to jump the whole two dimensional
 * array, which gives us a clue here. Right so I see this
 * pattern here, and it's that the code accesses data members
 * located right after the arrays. Putting into consideration
 * memory alignment, this problem becomes a harder challenge
 * because we have to figure out extra padding, so then we
 * could find the length of the arrays.
 * 
 * We could see that &q->array[B] + p_0 = &q->t, where p_0
 * is the padding between the last array element and t, s.t:
 *                  0 <= p_0 <= 3.
 * (C allows us pointers to point one past the end of array
 *  bounds).
 *
 * Same thing for &q->u = &q->s[A] + p_1, 0 <= p_1 <= 6.
 * Hence, we could find a range of the #define constants
 * based on the padding, and their alignments:
 *          5 <= B <= 8
 * and since &q->u = 8(%rsi) + A*2 + padding = 32(%rsi):
 *          9 <= A <= 12.
 * Okay, so I just attempted guessing B = 5, A = 9 and so
 * 5*9*4 = 180, which just happens to be perfectly in-line
 * with our ranges, just a 4-byte padding for alignment
 * that was required was all. Any other combinations
 * exceeded that number. Let's test these constants:
 *
    movslq 8(%rsi), %rax
 * This accesses the q->t, which is aligned to 4 bytes,
 * and so if B <= 4 then it would have been 4(%rsi).
 * Then:
 *
    long v2 = q->u;
    addq 32(%rsi), %rax
 * for A = 9: 8(%rsi) + 9*2 + padding = 26 + padding,
 * perfect.
 *
 *
    movq %rax, 184(%rdi)
 * This jumps the whole two dimensional array int x[A][B],
 * so it's A*B*sizeof(int) bytes = 180 + padding,
 * such that padding <= 4. So it's all aligned.
 */

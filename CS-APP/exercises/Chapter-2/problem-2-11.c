
/*
Armed with the function inplace_swap from Problem 2.10, you decide to write
code that will reverse the elements of an array by swapping elements from opposite
ends of the array, working toward the middle.
You arrive at the following function:

void reverse_array(int a[], int cnt) {
    int first, last;
    for (first = 0, last = cnt - 1;
         first <= last;
         first++, last--)
         inplace_swap(&a[first], &a[last]);
}

When you apply your function to an array containing elements 1, 2, 3, and 4,
you find the array now has, as expected, elements 4, 3, 2, and 1. When you try it
on an array with elements 1, 2, 3, 4, and 5, however, you are surprised to see that
the array now has elements 5, 4, 0, 2, and 1. In fact, you discover that the code
always works correctly on arrays of even length, but it sets the middle element to
0 whenever the array has odd length.

A. For an array of odd length cnt = 2k + 1, what are the values of variables
first and last in the final iteration of function reverse_array?

B. Why does this call to function inplace_swap set the array element to 0?

C. What simple modification to the code for reverse_array would eliminate
this problem?

Solutions:
A. The answer is k, that's because the moment of the last iteration,
   first = last is the floor of cnt/2, as in floor((2k+1)/2) = k
B. That's because when we call inplace_swap on the middle element,
   it is at the same index first = last, so the XOR operations are
   made on its own, directly leading to the zeroing of the middle
   element.
C. simply modify first <= last to first < last
*/

#include <stdio.h>

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void reverse_array(int a[], int cnt) {
    int first, last;
    for (first = 0, last = cnt - 1;
         first < last;
         first++, last--)
         inplace_swap(&a[first], &a[last]);
}

int main(void) {
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    int cnt = sizeof(a) / sizeof(a[0]);
    reverse_array(a, cnt);
    
    for (int i = 0; i < cnt; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}

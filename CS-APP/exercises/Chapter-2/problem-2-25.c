
/*
Practice Problem 2.25 (solution page 187)
Consider the following code that attempts to sum the elements of an array a, where
the number of elements is given by parameter length:

float sum_elements(float a[], unsigned length)
{
    int i;
    float result = 0;

    for (i = 0; i <= length - 1; i++)
        result += a[i];
    return result;
}

When run with argument length equal to 0, this code should return 0.0.
Instead, it encounters a memory error. Explain why this happens. Show how this
code can be corrected.
 */


/* 
Solution:
if we call the following functions with arguments:

sum_elements(a, 0);

the comparison in sum_elements i <= length - 1 actually results to i <= UINT_MAX
since length is unsigned and C promotion rules tells us if either operand of a
comparison is unsigned, both operands are casted to be unsigned. So length - 1
for length = 0 is actually (unsigned)-1 = UINT_MAX.
Then the function tries to read UINT_MAX bytes from a, and leads to a 
disaster. This code can be corrected by simply replacing the comparison
i <= length - 1 with i < length as long as i is positive.
*/

float sum_elements(float a[], unsigned length)
{
    int i;
    float result = 0;
    
    for (i = 0; i < length; i++)
        result += a[i];
    return result;
}

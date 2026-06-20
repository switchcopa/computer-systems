/*
In C, there is a strong relationship between pointers and arrays, strong enough that pointers
and arrays should be discussed simultaneously. Any operation that can be achieved by array
subscripting can also be done with pointers. The pointer version will in general be faster but, at
least to the uninitiated, somewhat harder to understand.
The declaration
*/

int a[10];

/*
defines an array of size 10, that is, a block of 10 consecutive objects named a[0], a[1],
..., a[9].
The notation a[i] refers to the i-th element of the array. If pa is a pointer to an integer,
declared as:
*/

int *pa;

/* 
then the assignment:
*/

pa = &a[0];

/*
sets pa to point to element zero of a; that is, pa contains the address of a[0].
Now the assignment:
*/

int x;
x = *pa;

/*
will copy the contents of a[0] into x.
If pa points to a particular element of an array, then by definition pa+1 points to the next
element, pa+i points i elements after pa, and pa-i points i elements before. Thus, if pa points
to a[0]
        *(pa + 1)
refers to the contents of a[1], pa+i is the address of a[i], and *(pa+i) is the contents of
a[i].
*/

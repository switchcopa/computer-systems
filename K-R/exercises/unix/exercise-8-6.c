

/* Exercise 8-6. The standard library function calloc(n, size) returns a pointer to n objects of size 'size',
 * with the storage iniitalized to zero. Write calloc, by calling malloc or by modifying it
 */

void *calloc(size_t size, size_t count)
{
    size_t bytes = size * count;
    void *mem = malloc(bytes);
    if (mem)
        memset(mem, 0, bytes);
    return mem;
}

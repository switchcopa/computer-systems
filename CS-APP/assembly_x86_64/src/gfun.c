
long int gfun(int x, int y) {
    long int t1 = (long)x + (long)y;
    long int t2 = (long)(x + y);
    return t1 | t2;
}

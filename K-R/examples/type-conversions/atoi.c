int atoi(char s[]) {
    int i, res;

    res = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; i++) 
        res = 10 * res + (s[i] - '0');
    
    return res;
}

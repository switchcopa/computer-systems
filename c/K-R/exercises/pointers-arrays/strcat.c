/* str_cat: copies string t to the end of s array version*/
void str_cat_arr(const char *s, char *t) {
        int i, j;
        
        for (i = 0; t[i] != '\0'; i++)
                ;
        for (j = 0; (t[i] = s[j]) != '\0'; i++, j++)
                ;
}

/* str_cat: copies string t to the end of s pointers version*/
void str_cat_ptr(const char *s, char *t) {
        while (*t != '\0')
                t++;

        while ((*t++ = *s++) != '\0')
                ;
}

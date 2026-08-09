// this is an example from The C programming language by K&R

void str_cat(char s[], char t[]) {
    int i, j; 

    i = j = 0;
    while (s[i++] != '\0')
    ;
    
    while ((s[i++] = t[j++]) != '\0')
    ;
}

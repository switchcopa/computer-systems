
/* str_len: return length of string s */
int str_len(const char *s) {
        int i;

        for (i = 0; *s != '\0'; s++)
                i++;

        return i;
}

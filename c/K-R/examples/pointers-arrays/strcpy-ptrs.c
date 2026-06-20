/* strcpy: copy t to s; pointer version */
void str_cpy(char *s, const char *t) {
        while ((*s++ = *t++) != '\0')
                ;
}

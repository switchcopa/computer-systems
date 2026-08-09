/* strcmp: return < 0 if s < t, 0 if s == t and > 0 if s > t */
int strcmp(const char* s, const char *t) {
        int i;

        for (i = 0; s[i] == t[i]; i++)
                if (s[i] == '\0')
                        return 0;

        return s[i] - t[i];
}

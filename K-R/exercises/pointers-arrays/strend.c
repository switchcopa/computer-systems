/* t = hello
 * s = cathello
 * strend(s, t) => 1
*/

/* strend(s, t): returns 1 if the string t occurs at the end of the string s, and zero otherwise. */
int strend(const char *s, const char *t) {
        const char *s_end = s;
        const char *t_end = t;

        while (*s_end != '\0')
                s_end++;

        while (*t_end != '\0')
                t_end++;
        
        while (t_end > t && s_end > s) {
                if (*--s_end != *--t_end)
                        return 0;
        }

        return (t_end == t);
}

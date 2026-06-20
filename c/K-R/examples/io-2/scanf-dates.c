
// Suppose we want to read input lines that contain dates of the form 
//
// 25 Dec 1998
// The scanf statement is:

int day, year;
char monthname[20];

scanf("%d %s %d", &day, monthname, year);

// Literal characters can appear in the scanf format string; they must
// match the same characters in the input. So we could read the dates
// of the form MM/DD/YY with the scanf statement:

int day, month, year;

scanf("%d/%d/%d", &day, &month, &year);
// scanf ignores blanks and tabs in its format string. Furthermore, it skips
// over white space as it looks for input values

// Final warning: the arguments to scanf and sscanf must be pointers. By far
// the most common error is writing

int n;
scanf("%d", n);
// instead of

scanf("%d", &n);

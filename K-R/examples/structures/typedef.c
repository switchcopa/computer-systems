
/* C provides a facility called typedef for creating new data type names. For example, the
declaration */ 

typedef int Length;

/* makes the name Length a synonym for int. The type Length can be used in declarations,
casts, etc., in exactly the same ways that the int type can be: */ 

Length len, maxlen;
Length *lengths[];

/* Similarly, the declaration */ 

typedef char *String;

/* makes String a synonym for char * or character pointer, which may then be used in
declarations and casts: */  

String p, lineptr[MAXLINES], alloc(int);
int strcmp(String, String);
p = (String) malloc(100);

/* for more documentation on the typedef keyword, see typedef K&R section */

#define XMAX 1400
#define YMAX 900

struct point
{
    int x;
    int y;
};

struct rect
{
    struct point pt1;
    struct point pt2;
};

/*
*
* The only legal operations on a structure are copying it or assigning to it as a unit, taking its
* address with &, and accessing its members. Copy and assignment include passing arguments to
* functions and returning values from functions as well. Structures may not be compared. A
* structure may be initialized by a list of constant member values; an automatic structure may
* also be initialized by an assignment.
* Let us investigate structures by writing some functions to manipulate points and rectangles.
* There are at least three possible approaches: pass components separately, pass an entire
* structure, or pass a pointer to it. Each has its good points and bad points.
* The first function, makepoint, will take two integers and return a point structure:
*/ 

/* makepoint: make a point from x and y components */
struct point makepoint(int x, int y)
{
    struct point pt;

    pt.x = x;
    pt.y = y;
    return pt;
}

// makepoint can now be used to initialize any structure dynamically, or to provide structure
// arguments to a function


int main(int argc, char **argv)
{
    struct rect screen;
    struct point middle;
    struct point makepoint(int, int);

    screen.pt1 = makepoint(0,0);
    screen.pt2 = makepoint(XMAX, YMAX);
    middle = makepoint((screen.pt1.x + screen.pt2.x) / 2,
                       (screen.pt1.y + screen.pt2.y) / 2);

// The next step is a set of functions to do arithmetic on points. For instance

    struct point addpoint(struct point, struct point);

/*
    Here both the arguments and the return value are structures. We incremented the components
    in p1 rather than using an explicit temporary variable to emphasize that structure parameters
    are passed by value like any others.
    As another example, the function ptinrect tests whether a point is inside a rectangle, where
    we have adopted the convention that a rectangle includes its left and bottom sides but not its
    top and right sides:
*/

    int ptinrect(struct point p, struct rect r);

/*
    This assumes that the rectangle is presented in a standard form where the pt1 coordinates are
    less than the pt2 coordinates. The following function returns a rectangle guaranteed to be in
    canonical form:
*/

    struct rect canonrect(struct rect r);

/* 
    Structure pointers are just like pointers to ordinary variables.
    The declaration
*/

    struct point *pp;

// says that pp is a pointer to a structure of type struct point. If pp points to a structure, then
// *pp is that structure, and (*pp).x, (*pp).y are the members. To use pp, we might write:

    struct point origin;
    pp = &origin;
    origin = makepoint(16, 69);

    printf("origin is (%d, %d)\n", (*pp).x, (*pp).y);
/* The parentheses are necessary in (*pp).x because the precedence of the structure member
    operator . is higher then *. The expression *pp.x means *(pp.x), which is illegal here
    because x is not a pointer.
*/

// pointers are so frequently used that an alternative notation is provided as a shorthand. If p is a 
// pointer to a structure, then 
//      p->member_of_structure
// refers to the particular member. So we could instead write

    printf("origin is (%d, %d)\n", pp->x, pp->y);

/*
    The structure operators . and ->, together with () for function calls and [] for subscripts, are
    at the top of the precedence hierarchy and thus bind very tightly. For example, given the
    declaration
*/

    struct {
        int len;
        char *str;
    } *p;
    
// then
    ++p->len;
// increments len, not p. Because the implied parenthesization is ++(p->len).
/*
    Parentheses can be used to alter binding: (++p)->len increments p before accessing len, and (p++)->len
    increments p afterward.
    In the same way, *p->str fetches whatever str points to; *p->str++ increments str after
    accessing whatever it points to (just like *s++); (*p->str)++ increments whatever str points
    to; and *p++->str increments p after accessing whatever str points to.
*/
}

struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}


int ptinrect(struct point p, struct rect r)
{
    return p.x >= r.pt1.x && p.x < r.pt2.x &&
            p.y >= r.pt1.y && p.y < r.pt2.y;
}

#define min(a,b) ((a) > (b) ? (b) : (a))
#define max(a,b) ((a) > (b) ? (a) : (b))

struct rect canonrect(struct rect r)
{
    struct rect temp;

    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}

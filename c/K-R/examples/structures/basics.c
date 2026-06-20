/* a structure is a collection of one or more variables, possibly of different types, grouped together
 * under a single name for conventional handling. It helps organize complex data, especially in large
 * projects. 
 * */ 

struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};

// the keyword struct introduces a structure declaration, which is a list of declarations enclosed in brackets
/*
    A structure declaration that is not followed by a list of variables reserves no storage; it merely
    describes a template or shape of a structure. If the declaration is tagged, however, the tag can
    be used later in definitions of instances of the structure. For example, given the declaration of
    point:
   */ 

struct point pt;
struct rect rectangle;

/* 
    defines a variable pt which is a structure of type struct point. A structure can be initialized
    by following its definition with a list of initializers, each a constant expression, for the
    members:
*/ 

struct point maxpt = {320, 200};

#include <stdio.h>
#include <math.h>

int main(void) {
// The structure member operator ``.'' connects the structure name and the member name. To
// print the coordinates of the point pt, for instance,
    pt.x = 420;
    pt.y = 67;

    printf("%d, %d\n", pt.x, pt.y);

// or compute the distance from the origin (0, 0) to pt:
    double dist, sqrt(double);
    dist = sqrt((double)pt.x * pt.x + (double)pt.y * pt.y);
// Structures can be nested. One representation of a rectangle is a pair of points that denote the
// diagonally opposite corners: 
    
// then:
    rectangle.pt1 = (struct point){255, 255};
// refers to the x coordinate of pt1 member of rectangle.
    return 0;
}

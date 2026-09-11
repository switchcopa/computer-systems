
int min3_clamped(int a, int b, int c, int floor) {
    int min_ab = (a > b) ? b : a;
    int min_abc = (c > min_ab) ? min_ab : c;
    int clamped = (floor > min_abc) ? floor : min_abc;
    return clamped;
}

/*
minimum_ab = a
compare a to b
minimum_ab = b if (b < a)

minimum_abc = minimum_ab
compare minimum_ab to c
minimum_abc = c if (c < minimum_ab)

clamped = minimum_abc
compare minimum_abc to floor
clamped = floor if (floor > minimum_abc)
return clamped
*/

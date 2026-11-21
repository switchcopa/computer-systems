
bool eq = (a && b) || (!a && !b);

bool xor = (a && !b) || (b && !a);

/* Or simply:
bool xor = !(a == b)
*/

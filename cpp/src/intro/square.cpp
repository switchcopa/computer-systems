#include <iostream>

using namespace std;

double square(double d)
{
    return d*d;
}

void print_square(double x)
{
    cout << "the square of " << x << " is " << square(x) << "\n";
}

int main()
{
    print_square(3.14);
}

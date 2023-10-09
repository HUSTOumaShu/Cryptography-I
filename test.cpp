#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

int main()
{
    long double delta = pow(2, 128) / pow(10, 9);
    long double deltax = 4 * pow(10, 12) / 200;
    cout << delta / (deltax * 86400 * 365) << endl;
}

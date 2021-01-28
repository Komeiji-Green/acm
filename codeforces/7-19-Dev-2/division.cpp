#include <iostream>
using namespace std;
void division(int a, int b, int &q, int &r);
int main()
{
    cout << -1 % 3 << endl;
    cout << -1 / 3 << endl;
    int a, b;
    int q, r;
    while (b != 0)
    {
        cin >> a;
        cin >> b;
        cout << (a / b) * b + a % b << endl;
        cout << (a / b) << " * " << b << " + " << a % b << " = " << a << endl;
        division(a, b, q, r);
        cout << q << " * " << b << " + " << r << " = " << a << endl;
        
    }
}

// a = b * q + r; !! require b > 0
void division(int a, int b, int &q, int &r)
{
    if(a >= 0) { q = a / b; r = a % b; }
    else if(a < 0) { q = a / b - 1; r = b + a % b; }
}
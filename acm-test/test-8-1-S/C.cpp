#include<iostream>
using namespace std;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll gao(ll m, ll n) { return m / gcd(m, n) * n}
int main()
{

}
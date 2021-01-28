#include<iostream>
#include<cstdio>
using namespace std;

typedef long long ll;
int main() {

    int T;
    cin >> T;
    ll a, b, c;
    while(T--) {
        scanf("%lld %lld %lld", &a, &b, &c);
        printf("%lld\n", a + b + c - 1);
    }
}
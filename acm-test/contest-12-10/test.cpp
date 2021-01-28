#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 25;
ll a[maxn], f[maxn];
int main() {
    f[0] = 1;
    for(ll i = 1; i <= 17; ++i) f[i] = i * f[i-1];
    a[0] = 1; a[1] = 1; a[2] = 2;
    //a[2]*(n-2)! + a[3]*(n-3)! + ... + a[n] = n!
    for(ll i = 3; i <= 17; ++i) {
        a[i] = f[i];
        for(int j = 2; j < i; ++j) {
            a[i] -= a[j] * f[i-j];
        }
    }
    for(int i = 1; i <= 17; ++i) printf("%lld\n", a[i]);
    
}
/**
 * 1 2 3
 * 1 3 2
 * 2 1 3 .
 * 2 3 1 
 * 3 1 2 .
 * 3 2 1 .
 * 
 * 1 2 3 4
 * 2 1 3 4 .
 * 
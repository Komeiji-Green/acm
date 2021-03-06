#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    int T;
    ll n;
    cin >> T;
    while(T--) {
        scanf("%lld", &n);
        while(n % 2 == 0) n /= 2;
        if(n > 1) { 
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}
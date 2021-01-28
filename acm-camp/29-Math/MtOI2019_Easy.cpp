#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a[1000050];
int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    ll sum = 0;
    for(int i = 1; i <= n; ++i) {
        sum ^= a[i];
    }
    printf("%lld\n", sum);
}
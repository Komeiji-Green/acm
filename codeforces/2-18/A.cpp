#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

ll a[N];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n ;++i) scanf("%lld", &a[i]);
        ll sum = 0, cur = 0;
        bool f = 1;
        for(int i = 1; i <= n; ++i) {
            sum += a[i];
            cur += i - 1;
            if(sum < cur) {
                f = 0; break;
            }
        }
        if(f) printf("Yes\n");
        else printf("No\n");
    }
}
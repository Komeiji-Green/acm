#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005 * 1005;
ll a[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, k, m;
        scanf("%d %d", &n, &k);
        m = n * k;
        for(int i = 1; i <= m; ++i) scanf("%d", &a[i]);
        int hf = (n+1)/2;
        int ii = k * (hf - 1) + 1;
        ll sum = 0;
        int gap = n - hf + 1;
        for(int i = ii; i <= m; i += gap) {
            sum += a[i];
        }
        printf("%lld\n", sum);
    }
}
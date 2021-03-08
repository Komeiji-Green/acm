#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1000007;
ll a[maxn], dp[maxn];
int pos[maxn][61];
int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) scanf("%lld", &a[i]);
    ll sum, ans = 0, cur;
    int sz = (1<<n);
    for(int i = 0; i < sz; ++i) {
        sum = 0, cur = 0;
        for(int j = 0; j < n; ++j) {
            if((1<<j)&i) {
                sum += (a[j] & cur);
                cur = a[j];
            }
        }
        ans = max(ans, sum);
    }
    printf("%lld\n", ans);
}
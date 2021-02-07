#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1000050;
const ll inf = 0x3f3f3f3f3f3f3f3f;
ll a[maxn];
ll q[maxn], l[maxn];
ll sumq[maxn], sum[maxn], dp[maxn];
void chk(ll &x, ll v) {
    if(x >= v) x = v;
}
int main() {
    int n; cin >> n;
    ll r1, r2, r3, d;
    cin >> r1 >> r2 >> r3 >> d;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for(int i = 1; i <= n; ++i) {
        q[i] = a[i] * min(r1, r3) + r3;
        l[i] = min(r2, a[i] * min(r1, r3) + r1) + min(r1, min(r2, r3));
    }
    for(int i = 1; i <= n; ++i) {
        sumq[i] = sumq[i-1] + q[i];
        sum[i] = sum[i-1] + min(q[i], l[i]);
    }
    ll minv = inf;
    /*for(int i = n; i >= 1; --i) {
        dp[i] = minv - sum[i-1] - d * i;
        minv = min(minv, d * i + sum[i] + sumq[n] - sumq[i]);
    }*/
    //printf("q: "); for(int i = 1; i <= n; ++i) printf("%lld ", q[i]); cout << endl;
    //printf("l: "); for(int i = 1; i <= n; ++i) printf("%lld ", l[i]); cout << endl;
    //printf("tt1: "); for(int i = 1; i <= n; ++i) printf("%lld ", dp[i]); printf("\n");
    minv = inf; dp[n+1] = 0;
    for(int i = n; i >= 1; --i) {
        //printf("%d: ", i);
        dp[i] = q[i] + dp[i+1];
        if(i < n) dp[i] = min(dp[i], d * (n - i) + sum[n-1] - sum[i-1] + q[n]);// printf("init: %lld ", dp[i]);
        dp[i] = min(dp[i], minv - sum[i-1] - 2 * d * i);
        minv = min(minv, sum[i] + 2 * d * i + dp[i+1]);
        
        //dp[i] = min(dp[i], minv - sum[i-1] - 2 * d * i);
        //minv = min(minv, sum[i-1] + 2 * d * (i-1) + dp[i]);
    }
    //printf("tt2: "); for(int i = 1; i <= n; ++i) printf("%lld ", dp[i]); printf("\n");
    ll ans = dp[1] + d * (n - 1);
    cout << ans << endl;
    
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 233333;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll a[maxn], dp[maxn], minv[maxn], stk1[maxn], stk2[maxn], pre[maxn], ft1, rr1, ft2, rr2; 
// key: dp[j] + pre[j - 1], i < j < i + k
int n, K; ll T;

struct QQ {
    // key : dp[j]
    // con : j - i > K && pre[j - 1] <= T + pre[i - 1]
    int ft, rr; int stk[maxn];
    void add(int j, int i) {
        if(j - i < K) return;
        while(ft < rr && dp[j] <= dp[stk[ft]]) ++ft;
        stk[--ft] = j;
        while(ft < rr && pre[stk[rr-1]-1] > T + pre[i-1]) --rr;
    }
    ll getmin() {
        return (ft < rr) ? dp[stk[rr-1]] : INF;
    }
} q2;

struct Q { 
    // key : dp[j] + pre[j - 1]
    // con : j - i <= K && pre[j - 1] <= T + pre[i - 1]
    int ft, rr; int stk[maxn];
    ll key(int x) {return dp[x] + pre[x - 1];}
    void add(int j, int i) {
        int tmp = ft;
        while(tmp < rr && key(j) <= key(stk[ft])) ++ft;
        stk[--ft] = j;
        while(ft < rr && (stk[rr-1]-i > K || pre[stk[rr-1]-1] > T + pre[i-1])) {
            --rr;
        }
    }
    ll getmin() {
        return (ft < rr) ? key(stk[rr-1]) : INF;
    }
} q1;

int main() {
    cin >> n >> K >> T;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    pre[0] = 0;
    for(int i = 1; i <= n; ++i) pre[i] = pre[i-1] + a[i];
    dp[n] = 0;
    q1.ft = q1.rr = q2.ft = q2.rr = n + 1;
    for(int i = n - 1; i >= 1; --i) {
        q1.add(i + 1, i);
        if(i + K + 1 <= n) q2.add(i + K + 1, i);

        dp[i] = min(min(q1.getmin()-pre[i-1], q2.getmin()),(pre[n]-pre[i-1] > T ? 2ll * (pre[n]-pre[i-1]) : 0ll));
        
        //for(int j = q1.ft; j < q1.rr; ++j) printf("%d ", q1.stk[j]);
        //printf("\n");
        //for(int j = q2.ft; j < q2.rr; ++j) printf("%d ", q2.stk[j]);
        //printf("\n");
        /*
        // 获得dp[i]
        if(ft1 < rr1) dp[i] = min(dp[stk[rr-1]] + pre[stk[rr-1] - 1] - pre[i-1], );

        // j - i < k && sum[i, j-1] < K
        while(ft1 < rr1 && (dp[stk[ft1]] + pre[stk[ft] - 1]) >= (dp[i] + pre[i-1])) ++ft1;
        st[--ft1] = i;
        while(ft1 < rr1 && (stk[rr1-1] >= i + K || stk[rr1-1])) 
        while(ft < rr && (dp[stk[ft]] + pre[stk[ft] - 1]) >= (dp[i] + pre[i - 1])) ++ft;
        stk[--ft] = i;
        while(ft < rr && stk[rr-1] >= i + K) --rr;  */
    }
    printf("%lld\n", dp[1]);
}
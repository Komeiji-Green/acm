#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
const ll INF = 0x3f3f3f3f;
vector<int> ch[maxn], li[maxn];
int d[maxn];
ll dp[maxn], a[maxn];
void change(int x, int dad) {
    li[d[x]].push_back(x);
    for(auto y : ch[x]) {
        if(y == dad) continue;
        d[y] = d[x] + 1;
        change(y, x);
    }
}


int main() {
    int T, n;
    cin >>  T;
    while(T--) {
        scanf("%d", &n);

        for(int i= 0; i<=n;++i) ch[i].clear(), li[i].clear();
        for(int i = 2, p; i <= n; ++i) {
            scanf("%d", &p);
            ch[i].push_back(p); ch[p].push_back(i);
        }
        for(int i=2;i<=n;++i) scanf("%lld", &a[i]);
        d[1] = 0;
        change(1, 0);
        int dep = 0;
        for(int i=  1; i<= n; ++i) {
            dep = max(dep, d[i]);
        }
        ll M = 0, m = INF, m1 = -INF, m2 = -INF;
        for(auto x : li[dep]) {
            dp[x] = 0;
            M = max(M, a[x]); m = min(m, a[x]);
            m1 = max(m1, dp[x] - a[x]); m2 = max(m2, dp[x] + a[x]);
        }
        for(int i = dep - 1; i >= 0; --i) {
            for(auto x : li[i]) {
                ll curM = 0, curm = INF, curm1 = -INF, curm2 = -INF;
                for(auto y : ch[x]) {
                    if(d[y] <= d[x]) continue;
                    curM = max(curM, a[y]);
                    curm = min(curm, a[y]);
                    curm1 = max(curm1, dp[y] - a[y]);
                    curm2 = max(curm2, dp[y] + a[y]);
                }
                dp[x] = max(max(curm1 + M, curm2 - m),max(m1 + curM, m2 - curm));
            }
            M = 0, m = INF, m1 = -INF, m2 = -INF;
            for(auto x : li[i]) {
                M = max(M, a[x]); m = min(m, a[x]);
                m1 = max(m1, dp[x] - a[x]); m2 = max(m2, dp[x] + a[x]);
            }
        }
        printf("%lld\n", dp[1]);

    }
}
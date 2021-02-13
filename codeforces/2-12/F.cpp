#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

const int maxn = 233333;
ll C[maxn];
int n;
void clear() {
    for(int i = 0; i <= n + 1; ++i) C[i] = 0;
}
void add(int x, ll v) {
    for(int i = x; i <= n + 1; i += i & (-i)) C[i] = (C[i] + v) % mod;
}
ll query(int x) {
    ll res = 0;
    for(int i = x; i; i -= i & (-i)) res = (res + C[i]) % mod;
    return res;
}
ll b[maxn], dp[maxn], pre[maxn], nxt[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
        dp[n + 1] = 1; b[0] = 0; pre[0] = 0;
        for(int i = 1; i <= n; ++i) pre[i] = (pre[i-1] + b[i]);
        map<ll, int> mp;
        for(int i = n; i >= 0; --i) {
            if(!mp.count(pre[i])) {
                nxt[i] = n + 1;
            } else {
                nxt[i] = mp[pre[i]];
            }
            mp[pre[i]] = i;
        }
        clear();
        add(n + 1, 1);
        for(int i = n; i >= 1; --i) {
            int k = nxt[i-1];
            if(k > n) k = n;
            dp[i] = query(k + 1);
            add(i, dp[i]);
        }
        printf("%lld\n", (dp[1] + mod) % mod);
    }
} 
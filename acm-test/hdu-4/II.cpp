#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1000007;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;
int f[N], invf[N], inv[N];
void init() {
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i < N; i++) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    f[0] = 1, invf[0] = 1;
    for(int i = 1; i < N; ++i) f[i] = 1ll * i * f[i-1] % mod, invf[i] = 1ll * inv[i] * invf[i-1] % mod;
}
int C(int n, int m) { // C(n, m)
    if(m > n || m < 0) return 0;
    return (1ll*f[n]*invf[m]%mod)*invf[n-m]%mod;
}
void precalc(int *dp, int n, int m, int L) {
    dp[n] = 0; if(m <= L) dp[n] = C(n, m);
    for(int i = n - 1; i >= 0; --i) {
        dp[i] = (dp[i+1]+1ll*C(i, L)*C(n-1-i, m-L-1)%mod)%mod;
    }
}

vector<int> vec[N];
int dp[2][N], siz[N], n, m, ans = 0;
void dfs(int x, int dad) {
    siz[x] = 1;
    for(auto y : vec[x]) {
        if(y == dad) continue;
        dfs(y, x);
        siz[x] += siz[y];
    }
    for(auto y : vec[x]) {
        if(y == dad) continue;
        int a = siz[y], b = n - a;
        ans = (0ll+ans+(1ll*a*dp[0][a-1]%mod)+(1ll*b*dp[1][b-1]%mod))%mod; 
    }
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    init();
    int T, u;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int i = 1; i <= n; ++i) vec[i].clear();
        for(int i = 2; i <= n; ++i) {
            cin >> u;
            vec[u].push_back(i); vec[i].push_back(u);
        }
        ans = 0;
        precalc(dp[0], n-1, m-1, (m/2)-1);
        precalc(dp[1], n-1, m-1, m-(m/2)-2);
        dfs(1, 0);
        cout << (ans+mod)%mod << endl;
    }
    
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1000000009;
const int x = 383008016;
const int invx = 276601605;
const int w1 = 691504013;
const int w2 = 308495997;

// 快速幂 计算 a^k % p
int Pow(int a, ll k) {
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % mod;
        k >>= 1; a = 1ll * a * a % mod;
    }
    return ans;
}

const int maxn = 100005;
int C[maxn], F[maxn], q[maxn], qN[maxn];
int main() {
    int T;
    cin >> T;
    ll N, c, K;
    int y1, y2, yy, yyN, ans;
    while(T--) {
        scanf("%lld %lld %lld", &N, &c, &K);
        y1 = Pow(w1, c); y2 = Pow(w2, c);
        C[0] = (K % 2 == 0) ? 1 : -1;
        for(int i = 0; i < K; ++i) {
            C[i+1] = 1ll * (1ll * (i - K) * Pow(i + 1, mod - 2) % mod) * C[i] % mod;
        }

        yy = 1ll * y1 * Pow(y2, mod - 2) % mod;
        yyN = Pow(yy, N + 1);
        q[0] = Pow(y2, K);
        qN[0] = Pow(q[0], N + 1);
        for(int i = 0; i < K; ++i) {
            q[i + 1] = 1ll * yy * q[i] % mod;
            qN[i + 1] = 1ll * yyN * qN[i] % mod;
        }
        for(int i = 0; i <= K; ++i) {
            if((q[i] - 1) % mod == 0) {
                F[i] = (N + 1) % mod;
            } else {
                F[i] = 1ll * (qN[i] - 1) * Pow(q[i] - 1, mod - 2) % mod;
            }
        }
        ans = 0;
        for(int i = 0; i <= K; ++i) {
            ans = (ans + 1ll * C[i] * F[i] % mod) % mod;
        }
        ans = 1ll * ans * Pow(invx, K) % mod;
        printf("%d\n", (ans + mod) % mod);
    }
}
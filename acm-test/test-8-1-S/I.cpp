#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

const int maxn = 100000 + 5;

int v[maxn];

int sum1[maxn];
int sum2[maxn];

int f[maxn];    // 并查集

int Find(int x) {
    if(f[x] == x) return x;
    return f[x] = Find(f[x]);
}

void Union(int x, int y) {
    int fx = Find(x);
    int fy = Find(y);
    f[fx] = fy;
}

int Pow(int a, int k, int p) {
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

int C(int m, int n, int p) {
    int fm = 1;
    for(int x = m; x > m - n; x--)
        fm = 1ll * fm * x % p;
    int fn = 1;
    for(int x = 1; x <= n; x++)
        fn = 1ll * fn * x % p;

    return 1ll * fm * Pow(fn, p - 2, p) % p;
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;

        int all1 = 0;
        int all2 = 0;
        memset(sum1, 0, sizeof(sum1));
        memset(sum2, 0, sizeof(sum2));
        for(int i = 1; i <= n; i++) {
            scanf("%d", &v[i]);
            if(v[i] == 1) { sum1[i] = 1; all1++; }
            if(v[i] == 2) { sum2[i] = 1; all2++; }
        }

        for(int i = 1; i <= n; i++) {
            f[i] = i;
        }

        ll cnt = (1ll * C(all2, 3, mod) + 1ll * all1 * C(all2, 2, mod) % mod) % mod;
        printf("%d\n", cnt);

        // 核心思想：计算每次操作后，由合法小队变成非法小队的个数
        int u, v;
        for(int i = 0; i < n - 1; i++) {
            scanf("%d %d", &u, &v);
            int fu = Find(u);
            int fv = Find(v);
            if(fu != fv) {
                int sum1_rest = all1 - sum1[fu] - sum1[fv];
                int sum2_rest = all2 - sum2[fu] - sum2[fv];
                int sum_rest = sum1_rest + sum2_rest;
                cnt = (1ll * cnt - 1ll * (1ll * sum2[fu] * sum2[fv] % mod) * sum_rest % mod
                        - 1ll * sum2_rest * (1ll * sum1[fu] * sum2[fv] % mod + 1ll * sum1[fv] * sum2[fu] % mod) % mod) % mod;
                f[fu] = fv;
                sum1[fv] += sum1[fu];
                sum2[fv] += sum2[fu];
            }
            printf("%d\n", (cnt < 0 ? cnt + mod : cnt));
        }
    }
}
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;
typedef long long ll;
#pragma comment(linker, "/STACK:102400000,102400000")
#pragma optimize(2)


const ll mod = 1e9 + 7;

inline void add(ll &x, ll y) {
    (x += y) >= mod && (x -= mod);
    (x < 0) && (x += mod);
}

const ll inv2 = (mod + 1) / 2;
const int N = 1000333;
ll f[N], invf[N], inv[N];
void init() {
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i < N; i++) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    f[0] = 1, invf[0] = 1;
    for(int i = 1; i < N; ++i) f[i] = i * f[i-1] % mod, invf[i] = inv[i] * invf[i-1] % mod;
}
ll C(int n, int m) { // C(n, m)
    if(m > n || m < 0) return 0;
    return ((f[n] * invf[m]) % mod) * invf[n-m] % mod;
}
// a + b == n, 总共选s, a中至少选k个
void precalc(ll *dp, int n, int s, int k) {
    dp[0] = k == 0 ? C(n, s) : 0;
    for(int i = 1; i <= n; ++i) {
        dp[i] = (dp[i-1] + C(i-1, k-1) * C(n-i, s-k) % mod) % mod;
    }
}

int n;
ll su[N], sz[N], dp[2][2][N];
ll calc(int k, int m, int op, int L, ll all) { 
    ll res = all * C(n - 2, m - 1) % mod;
    (res < 0) && (res += mod);
    auto cnt = dp[op];
    for(int i = 1; i <= k; ++i) {
        add(res, -su[i]*cnt[0][sz[i]-1]%mod);
        add(res, -(all-su[i])*cnt[1][sz[i]]%mod);
        //res = (res - (su[i] * cnt[0][sz[i]-1] % mod) - (all-su[i]) * cnt[1][sz[i]]) % mod;
    }
    return res;
}

int m;
vector<int> vec[N];

ll siz[N], sum[N], ans1, ans[N];
void change(int x, int dad) {
    siz[x] = 1; sum[x] = 0;
    for(auto y : vec[x]) {
        if(y == dad) continue;
        change(y, x);
        siz[x] += siz[y]; sum[x] += sum[y] + siz[y]; sum[x] %= mod;
    }
}
void dfs(int x, int dad, ll head) {
    int num = vec[x].size();
    head += (n - siz[x]); head %= mod;
    for(int i = 1; i <= num; ++i) {
        int y = vec[x][i-1];
        if(y == dad) sz[i] = n - siz[x], su[i] = head;
        else sz[i] = siz[y], su[i] = (sum[y] + siz[y]) % mod;
    }

    /*printf("id: %d\n", x);
    printf("head: %lld\n", head);
    for(int i = 1; i <= num; ++i) {
        printf("sz: %lld, su: %lld\n", sz[i], su[i]);
    }
    printf("\n");*/
    ll all = 0; for(int i = 1; i <= num; ++i) add(all, su[i]); //all = (all + su[i]) % mod;
    ans[x] = 0;
    int hf = (m>>1);
    if(m&1) {
        add(ans[x], calc(num, m - 1, 0, hf + 1, all));
        add(ans[x], calc(n
        um, m, 1, hf + 1, all));
    } else {
        for(int i = 1; i <= num; ++i) {
            ans1 = (ans1 + ((su[i] * C(sz[i]-1, hf-1)) % mod) * C(n-1-sz[i], hf-1) % mod +
                        ((all-su[i]) * C(sz[i], hf) % mod) * C(n-2-sz[i], hf-2) % mod) % mod;
        }
        add(ans[x], calc(num, m - 1, 0, hf, all));
        add(ans[x], calc(num, m, 1, hf, all));
        ll cur = 0;
        for(int i = 1; i <= num; ++i) {
            cur = (cur + su[i] * C(sz[i]-1, hf-1) % mod) % mod;
        }
        cur = cur * (num - 1) % mod;
        ans[x] = (ans[x] + cur) % mod;
    }
    for(int i = 1; i <= num; ++i) {
        int y = vec[x][i-1];
        if(y == dad) continue;
        dfs(y, x, (all - su[i] + mod) % mod);
    }
}
int main() {
    srand(time(NULL));
    clock_t stt = clock(), edd;
    init();
    int T, u;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) vec[i].clear();
        for(int i = 2; i <= n; ++i) {
            //scanf("%d", &u);
            u = i - 1;
            //u = rand() % (i - 1) + 1;
            vec[u].push_back(i); vec[i].push_back(u);
        }
        change(1, 0);
        ll res = 0; ans1 = 0;
        if(m == 1) { res = 0; }
        else if(m % 2) {
            precalc(dp[0][0], n - 2, m - 2, m / 2);
            precalc(dp[0][1], n - 2, m - 2, m / 2 + 1);
            precalc(dp[1][0], n - 2, m - 1, m / 2);
            precalc(dp[1][1], n - 2, m - 1, m / 2 + 1);
            dfs(1, 0, 0);
        } else {
            precalc(dp[0][0], n - 2, m - 2, m / 2 - 1);
            precalc(dp[0][1], n - 2, m - 2, m / 2);
            precalc(dp[1][0], n - 2, m - 1, m / 2 - 1);
            precalc(dp[1][1], n - 2, m - 1, m / 2);
            dfs(1, 0, 0);
            res = ans1 * inv2 % mod;
        }
        for(int i = 1; i <= n; ++i) res = (res + ans[i]) % mod;
        printf("%lld\n", (res + mod) % mod);
    }
    edd = clock();
    cout << (double)(edd-stt)/1000<<endl;
}
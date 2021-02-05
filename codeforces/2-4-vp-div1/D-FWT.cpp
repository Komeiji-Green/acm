#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const ll inv2 = (mod + 1) / 2;

ll Pow(ll a, ll k) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % mod;
        k >>= 1; a = a * a % mod;
    }
    return ans;
}

void FWT(ll *a, int len, int inv) {
    ll x, y;
    for(int h = 1; h < len; h <<= 1) {
        for(int i = 0; i < len; i += (h << 1)) {
            for(int j = 0; j < h; ++j) {
                x = a[i+j], y = a[i+j+h];
                a[i+j] = (x+y)%mod, a[i+j+h] = (x-y)%mod;
                if(inv == -1) a[i+j] = a[i+j] * inv2 % mod, a[i+j+h] = a[i+j+h] * inv2 % mod;
            }
        }
    }
}

const int N = 233333, M = 233333;
struct Edge {
    int to, pre;
} e[M];
int last[N], tot;
void ine(int a, int b) {
    ++tot;
    e[tot].to = b; e[tot].pre = last[a];
    last[a] = tot;
}

int b[N], deg[N], cnt;
int sg[N];
ll c[N], Y[N], X[N];
int main() {
    int n, m, uu, v;
    cin >> n >> m;
    while(m--) {
        scanf("%d %d", &uu, &v);
        ine(uu, v);
        ++deg[v];
    }
    queue<int> q;
    for(int i = 1; i <= n; ++i) {
        if(!deg[i]) q.push(i);
    }
    while(!q.empty()) {
        int x = q.front(); q.pop();
        b[++cnt] = x;
        for(int i = last[x]; i; i = e[i].pre) {
            int y = e[i].to;
            if(!(--deg[y])) q.push(y);
        }
    }
    sg[b[n]] = 0;
    for(int i = n - 1; i >= 1; --i) {
        int x = b[i];
        set<int> tr;
        for(int j = last[x]; j; j = e[j].pre) {
            int y = e[j].to;
            tr.insert(sg[y]);
        }
        int mex = 0;
        while(tr.count(mex)) ++mex;
        sg[x] = mex;
        //if(mex >= L) return 0;
    }
    for(int x = 1; x <= n; ++x) {
        c[sg[x]]++;
    }
    int len;
    for(len = 1; len < n; len <<= 1);

    ll invn = Pow(n + 1, mod - 2);
    for(int i = 0; i < len; ++i) c[i] = c[i] * invn % mod;
    c[0] = (c[0] - 1) % mod;
    FWT(c, len, 1);
    Y[0] = -invn;
    FWT(Y, len, 1);
    for(int i = 0; i < len; ++i) X[i] = Y[i] * Pow(c[i], mod - 2) % mod;
    FWT(X, len, -1);
    ll ans = (1 - X[0]) % mod;
    printf("%lld\n", (ans + mod) % mod);
}
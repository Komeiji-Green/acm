#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

ll Pow(ll a, ll k) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % mod;
        k >>= 1; a = a * a % mod;
    }
    return ans;
}

const int L = 512;
ll a[L][L+1], ans[L];
void gauss(int n, int m) { // 消增广矩阵
    vector<int> pos(m, -1);
    ll inv, del;
    for(int r = 0, c = 0; c < m; ++c) {
        int sig = -1;
        for(int i = r; i < n; ++i) 
            if(a[i][c]) {
                sig = i; break;
            }
        if(sig == -1) continue;
        pos[c] = r;
        if(sig != r) swap(a[sig], a[r]);
        inv = Pow(a[r][c], mod - 2);
        for(int i = 0; i < n; ++i) {
            if(i == r) continue;
            del = inv * a[i][c] % mod;
            for(int j = c; j <= m; ++j) a[i][j] = (a[i][j] - del * a[r][j] % mod) % mod; 
        }
        ++r;
    }
    for(int i = 0; i < m; ++i) {
        if(pos[i] != -1) {
            ans[i] = Pow(a[pos[i]][i], mod - 2) * a[pos[i]][m] % mod;
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
ll c[L];
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
    ll invn = Pow(n + 1, mod - 2);
    for(int i = 0; i < L; ++i) for(int j = 0; j < L; ++j) {
        a[i][j] = c[i^j] * invn % mod;
        if(i == j) a[i][j] = (a[i][j] - 1) % mod;
    }
    a[0][L] = -invn;
    //mat.a[0][L] = invn;
    gauss(L, L);
    ll res = (1 - ans[0]) % mod;
    printf("%lld\n", (res + mod) % mod);
    
}
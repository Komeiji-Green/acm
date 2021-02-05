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
struct Mat {
    ll a[L][L+1]; // 增广矩阵
    int n;
    ll guass() { // 行初等变换
        ll inv, ratio;
        for(int j = 0, sig; j < n; ++j) {
            sig = -1;
            for(int i = j; i < n; ++i) if(a[i][r]) {
                sig = i; break;
            }
            if(sig != r) {
                for(int k = r; k <= n; ++k) swap(a[r][k], a[sig][k]);
            }
            //if(a[r][r] == 0) return 0;
            inv = Pow(a[r][r], mod - 2);
            for(int i = 0; i < n; ++i) {
                if(i == r) continue;
                ratio = a[i][r] * inv % mod;
                a[i][r] = 0;
                for(int k = r + 1; k <= n; ++k) {
                    a[i][k] = (a[i][k] - a[r][k] * ratio % mod) % mod;
                }
            }
        }
        inv = Pow(a[0][0], mod - 2);
        return (mod - inv * a[0][n] % mod) % mod;
    }
} mat;

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

int a[N], deg[N], cnt;
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
        a[++cnt] = x;
        for(int i = last[x]; i; i = e[i].pre) {
            int y = e[i].to;
            if(!(--deg[y])) q.push(y);
        }
    }
    sg[a[n]] = 0;
    for(int i = n - 1; i >= 1; --i) {
        int x = a[i];
        vector<int> vec;
        for(int j = last[x]; j; j = e[j].pre) {
            int y = e[j].to;
            vec.push_back(sg[y]);
        }
        sort(vec.begin(), vec.end());
        int mex = 0;
        for(auto u : vec) {
            if(u == mex) ++mex;
            else break;
        }
        sg[x] = mex;
        //if(mex >= L) return 0;
    }
    for(int x = 1; x <= n; ++x) {
        c[sg[x]]++;
    }
    ll invn = Pow(n + 1, mod - 2);
    ll del = n * invn % mod;
    mat.n = L;
    for(int i = 0; i < L; ++i) for(int j = 0; j < L; ++j) {
        mat.a[i][j] = c[i^j] * invn % mod;
        if(i == j) mat.a[i][j] = (mat.a[i][j] - 1) % mod;
    }
    for(int i = 1; i < L; ++i) mat.a[i][L] = invn;
    //mat.a[0][L] = invn;
    ll ans = mat.guass();
    printf("%lld\n", (ans + mod) % mod);
    
}
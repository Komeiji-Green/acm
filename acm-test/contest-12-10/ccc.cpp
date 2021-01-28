#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;

int n, m;
int G[20][20], adj[20][20], deg[20];
int cnt[18][18];
struct state {
    uint w[18];
    void print() {
        bool flag = true;
        for(int i = 1; i <= n; ++i) {
            if(!w[i]) {printf("-1\t"); flag = false;}
            for(int j = 0; j <= n; ++j) {
                if((1<<j)&w[i]) { printf("%d\t", j); break; }
            }
        }
        if(flag) printf("haoye ");
    }
} st, ps;
uint bit[30];

struct cmp {
    bool operator()(const state& a, const state& b) const {
        for(int i = 1; i <= n; ++i) if(a.w[i] != b.w[i]) return false;
        return true;
    }
};
struct _hash {
    size_t operator()(const state& st) const {
        size_t res = st.w[1];
        for(int i = 2; i <= n; ++i) {
            res *= 19260817; res += st.w[i];
        }
        return res;
    }
};
unordered_map<state, ll, _hash, cmp> hsh, vis;

ll dfs(int num) {
    if(vis.count(ps)) { 
        //ps.print(); cout << "no" << endl; 
        return 0; 
    }
    //ps.print(); cout << endl;
    if(num == 0) return vis[ps] = 1;
    //if(hsh.count(st)) { printf("!!%lld\n", hsh[st]); return vis[ps] = hsh[st]; } 
    ll cur = 0; uint lbd, tmp, rem[18];
    for(int i = 1, sz; i <= n; ++i) if(st.w[i]) {
        tmp = st.w[i]; lbd = (st.w[i] & (-st.w[i])); 
        st.w[i] = 0; ps.w[i] = lbd;

        sz = deg[i];
        for(int j = 1; j <= sz; ++j) rem[j] = st.w[adj[i][j]], st.w[adj[i][j]] &= (~lbd);
        cur += dfs(num - 1);
        for(int j = 1; j <= sz; ++j) st.w[adj[i][j]] = rem[j];
        st.w[i] = tmp; ps.w[i] = 0;
    }
    return vis[ps] = cur;
}
int main() {
    for(int i = 0; i < 30; ++i) bit[i] = (1<<i);
    cin >> n >> m;
    int u, v;
    for(int i = 1; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }
    for(int i = 1; i <= n; ++i) {
        int c = 0;
        for(int j = 1; j <= n; ++j) if(G[i][j]) adj[i][++c] = j;
        deg[i] = c;
    }
    for(int i = 1; i <= n; ++i) st.w[i] = -1;
    ll ans = dfs(n);
    printf("%lld\n", ans);
}

// 0 1 0 1 0
// 0 1 0 1 0 chong
// 0 1 2 0 1
// 0 1 2 0 1 chong
// 0 1 0 1 0 chong
// 0 1 0 1 0 chong
// 0 2 1 0 1
// 0     0 1
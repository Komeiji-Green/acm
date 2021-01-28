#include<bits/stdc++.h>
using namespace std;

int Pow(int a, int k, int p) {
    int ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

const double eps = 1e-8;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

const int mod = 31011;
const int maxn = 2333;

const int N = 20;
struct Mat {
    int a[N][N], n, m;
    // 小模数int，记得改溢出！！！
    void set(int _n, int _m, int val) {
        n = _n, m = _m;
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) a[i][j] = val;
    }
    int guass() { // 辗转相除化简(当int, mod大时可能会溢出)
        int ans = 1;
        for(int j = 0; j < m; ++j) {
            for(int i = j + 1; i < n; ++i) {
                while(a[i][j]) {
                    int t = a[j][j] / a[i][j];
                    for(int k = j; k < m; ++k)
                        a[j][k] = (a[j][k] - t * a[i][k] % mod + mod) % mod; 
                    swap(a[i], a[j]);
                    ans = -ans;
                }
            }
        }
        for(int i = 0; i < m && i < n; ++i) ans = ans * a[i][i] % mod;
        return (ans + mod) % mod;
    }
} mat;

struct Edge {
    int u, v, w;
    bool operator<(const Edge &b) {
        return w < b.w;
    }
} e[maxn];

int f[maxn];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
void merge(int x, int y) {
    int fx = find(x); int fy = find(y);
    f[fx] = fy;
}

int cc[maxn], t1;       // 当前连通分量
int ncc[maxn], t2;      // 下一刻连通分量  
vector<int> adj[maxn];  // 邻接表
int deg[maxn];          // 度数
vector<int> ch[maxn];   // 新连通分量原来包含哪些子连通分量
int id[maxn];

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    sort(e + 1, e + m + 1);
    int ans = 1, cur = 1;
    int cnt = 0; bool flag = true;
    for(int i = 1; i <= n; ++i) f[i] = i;
    for(int i = 1; i <= m; ++i) merge(e[i].u, e[i].v);
    for(int i = 1; i <= n; ++i) if(f[i] == i) ++cnt;
    if(cnt > 1) ans = 0;
    else {
        for(int i = 1; i <= n; ++i) f[i] = i;
        t1 = n;
        for(int i = 0; i < t1; ++i) cc[i] = i + 1;
        for(int i = 1, last = 1; i <= m; ++i) {
            if(i == m || e[i].w != e[i+1].w) {  // 段尾
                for(int j = last; j <= i; ++j) {    // 建图
                    int u = find(e[j].u);
                    int v = find(e[j].v);
                    if(u == v) continue;
                    ++deg[u]; ++deg[v];
                    adj[u].push_back(v); adj[v].push_back(u);
                    //printf("%d: %d\n", u, v);
                }
                for(int j = last; j <= i; ++j) {
                    merge(e[j].u, e[j].v);
                }
                t2 = 0;
                for(int x = 0; x < t1; ++x) {
                    //printf("%d ", cc[x]);
                    ncc[t2] = find(cc[x]);
                    ch[ncc[t2]].push_back(cc[x]);
                    ++t2;
                }
                //printf("\n");
                sort(ncc, ncc + t2);
                t2 = unique(ncc, ncc + t2) - ncc;
                cur = 1;
                for(int k = 0, sz; k < t2; ++k) {
                    vector<int>&chl = ch[ncc[k]];
                    sz = chl.size();
                    if(sz <= 1) continue;
                    mat.set(sz, sz, 0);
                    for(int x = 0; x < sz; ++x) {
                        id[chl[x]] = x;
                    }
                    for(int x = 0; x < sz; ++x) {
                        for(auto ry : adj[chl[x]]) {
                            mat.a[x][id[ry]] -= 1;
                            //printf("(%d, %d) ", x, id[ry]);
                        }
                        //printf("\n");
                    }
                    for(int x = 0; x < sz; ++x) {
                        mat.a[x][x] = deg[chl[x]];
                    }
                    mat.n = mat.m = sz - 1;
                    cur = cur * mat.guass() % mod;
                }
                ans = ans * cur % mod;
                for(int x = 0; x < t1; ++x) {
                    adj[cc[x]].clear();
                    deg[cc[x]] = 0;
                }
                for(int y = 0; y < t2; ++y) {
                    ch[ncc[y]].clear();
                    cc[y] = ncc[y];
                }
                t1 = t2;
                t2 = 0;
                last = i + 1;
            }
        }
    }
    printf("%d\n", (ans + mod) % mod);
}

/*
3 -1 -1
-1 3 -1
-1 -1 2
*/
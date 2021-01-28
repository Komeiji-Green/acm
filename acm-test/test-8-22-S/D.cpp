#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;
typedef long long ll;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)
const int N = 300500;

const int mod = 998244353;

typedef long long ll;

const int M = 600500;

struct Edge {
    int from, to, pre;
    ll w;
};


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

Edge ee[M];
int la[N];
int es = 0;

void ine3(int a, int b, ll w) {
    es++;
    ee[es].from = a; ee[es].to = b; ee[es].w = w;
    ee[es].pre = la[a];
    la[a] = es;
}

inline void ine4(int a, int b, ll w) { ine3(a, b, w); ine3(b, a, w); } 

int n;

//int size[N]; // 子树大小
int dep[N]; // 深度
int anc[N][30]; // 祖先
//int minv[N][30]; // 最小权
int lg;

// dad是用来防止重复遍历的
void change(int x, int dad, int dept) {
    //size[x] = 1;
    dep[x] = dept;
    for(lg = 0; lg <= 20; lg++) if(n < (1 << (lg - 1))) break;
    rep(i, 1, lg) {
        if(dep[x] < (1 << i)) break;
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
        //minv[x][i] = min(minv[x][i - 1], minv[anc[x][i - 1]][i - 1]);
    }
    for(int i = la[x]; i; i = ee[i].pre) {
        int y = ee[i].to;
        if(y == dad) continue;
        anc[y][0] = x;
        //minv[y][0] = ee[i].w;
        change(y, x, dept + 1);
        //size[x] += size[y];
    }
}

// 倍增
int lca(int a, int b) {
    for(lg = 1; lg <= 20; lg++) if((1 << (lg - 1)) > n) break;
    if(dep[a] > dep[b]) swap(a, b);
    int d = dep[b] - dep[a];
    for(int i = lg; i >= 0; i--) {
        if(dep[b] < (1 << i)) continue;
        if((1 << i) & d) b = anc[b][i];
    }
    for(int i = lg; i >= 0; i--) {
        if(dep[a] < (1 << i)) continue;
        if(anc[a][i] != anc[b][i]) {
            a = anc[a][i]; b = anc[b][i];
        }
    }
    if(a != b)
        a = anc[a][0], b = anc[b][0];
    return a;
}


int sum[51][N];
int num[51][N];

int main()
{

    scanf("%d", &n);


    /*clock_t st, ed;
    st = clock();*/

    rep(i, 1, n) {
        num[1][i] = i;
        sum[1][i] = sum[1][i - 1] + num[1][i];
    }
    rep(k, 2, 50) {
        rep(i, 1, n) {
            num[k][i] = 1ll * num[k - 1][i] * i % mod;
            sum[k][i] = (sum[k][i - 1] + num[k][i]) % mod;
        }
    }

    int u, v;
    rep(i, 1, n - 1) {
        scanf("%d %d", &u, &v);
        ine4(u, v, 0);
    }

    change(1, 0, 1);

    int m, t;
    scanf("%d", &m);
    rep(i, 1, m) {
        scanf("%d %d %d", &u, &v, &t);
        int f = lca(u, v);
        int du = dep[u] - 1;
        int dv = dep[v] - 1;
        int df = dep[f] - 1;
        int dff = df > 0 ? df - 1 : 0;
        int ans = ((sum[t][du] - sum[t][df]) % mod + (sum[t][dv] - sum[t][dff]) % mod) % mod;
        ans = (ans + mod) % mod;
        printf("%d\n", ans);
    }


    /*ed = clock();
    cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;*/
}
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int M = 100500;
const int N = 50500;


struct Edge
{
    int from, to, pre, w;

} e[M]; //边集数组
int tot = 0;
int last[N];    // 表头


void ine(int a, int b, ll w) { // 有向图, a-->b
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w; e[tot].pre = last[a];
    last[a] = tot;
} 

// 无向图
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for (int i = last[x]; i; i = e[i].pre)
#define rep(i, a, b) for (int i = a; i <= b; i++)




int f[N];

int find(int x)
{
    if (f[x] == x)
        return x;
    return f[x] = find(f[x]);
}

void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    f[fx] = fy;
}

int n;

struct cmp {
    bool operator() (const Edge&lhs, const Edge& rhs) {
        return lhs.w > rhs.w;
    }
};

ll Kruskal(int n) {
    sort(e + 1, e + tot + 1, cmp());
    ll ans = 0;
    for(int i = 1, u, v; i <= tot; i++) {
        u = e[i].from, v = e[i].to;
        int fu = find(u), fv = find(v);
        if(fu == fv) continue;
        f[fu] = fv;
        ans += e[i].w;
    }
    return 1ll * n * 10000 - ans;
}



#define fill(a, x) { memset(a, x, sizeof(a)); }
void init()
{
    tot = 0;
    fill(last, 0);
    for(int i = 1; i <= n; i++) {
        f[i] = i;
    }
}
int main()
{
    int T;
    cin >> T;
    while(T--) {
        int boy, girl, R;
        cin >> girl >> boy;
        n = girl + boy;
        cin >> R;

        init();
        for(int i = 1, x, y, d; i <= R; i++) {
            scanf("%d %d %d", &x, &y, &d);
            ine2(x + 1, girl + y + 1, d);
        }
        cout << Kruskal() << endl;
    }
}
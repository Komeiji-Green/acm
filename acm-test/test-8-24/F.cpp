#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll IINF = 0x3f3f3f3f3f3f3f3f;
const int M = 50000;
const int N = 3000;
// 最小费用流

struct Edge {
    int from, to, w, pre;
    ll c;
} e[M];
int last[N];

int tot = 1;
inline void ine(int from, int to, int w, ll c)
{
    e[++tot].to = to;
    e[tot].w = w;
    e[tot].c = c;
    e[tot].from = from;
    e[tot].pre = last[from];
    last[from] = tot;
}

void ine2(int a, int b, int w, ll c) {
    ine(a, b, w, c);
    ine(b, a, w, c);
}

inline void add(int a, int b, int w, ll c) {
    ine(a, b, w, c);
    ine(b, a, 0, -c);
}

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


int s, t;
int fa[N], flow[N], inq[N];
ll dis[N];
queue<int> Q;
bool SPFA()
{
    while (!Q.empty())
        Q.pop();
    memset(fa, 0, sizeof(fa));
    memset(inq, 0, sizeof(inq));
    //memset(flow, 0x3f, sizeof(flow));
    memset(dis, 0xcf, sizeof(dis));
    //rep(i, 1, n) dis[i] = IINF;
    flow[s] = INF;
    //0xcf;
    dis[s] = 0;
    Q.push(s); inq[s] = 1;
    while (!Q.empty())
    {
        //printf("....\n");
        int cur = Q.front(); Q.pop();
        inq[cur] = 0;
        for (int eg = last[cur]; eg; eg = e[eg].pre)
        {
            int to = e[eg].to, vol = e[eg].w;
            if (vol > 0 && dis[to] < dis[cur] + e[eg].c) // 容量大于0才增广
            {
                //printf("%d %d, %lld < %lld + %lld\n", cur, to, dis[to], dis[cur], e[eg].c);
                fa[to] = eg; // 记录上一条边
                flow[to] = min(flow[cur], vol); // 更新下一个点的流量
                dis[to] = dis[cur] + e[eg].c; 
                if (!inq[to])
                {
                    Q.push(to);
                    inq[to] = 1;
                }
            }
        }
    }
    //cout << "spfa" << endl;
    return fa[t] != 0;
}

int maxflow;
ll maxcost;
inline void MCMF() 
{
    memset(flow, 0, sizeof(flow));
    maxflow = 0, maxcost = 0;
    while (SPFA())
    {
        for(int i = 1; i <= t; i++)
            printf("%d: %lld\n", i, dis[i]);
        //printf("%d %d\n", dis[t], flow[t]);
        if(maxcost + 1ll * dis[t] * flow[t] < 0) {
            maxflow += (maxcost / abs(dis[t]));
            break;
        }
        maxflow += flow[t];
        maxcost += dis[t] * 1ll * flow[t];
        for (int i = t; i != s; i = e[fa[i] ^ 1].to)
        {
            e[fa[i]].w -= flow[t];
            e[fa[i] ^ 1].w += flow[t];
        }
    }
}

const int maxn = 1000;
int p[maxn]; // 素因子
int l[maxn]; // 重数
int cnt = 0;

// 素因数分解 
void Fact(int x) 
{
    cnt = 0;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            p[++cnt] = i; l[cnt] = 0;
            while(x % i == 0) {
                x /= i; 
                l[cnt]++;
            }
        }
    }
    if(x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[++cnt] = x; l[cnt] = 1;
    }
}

// 二分图染色 
int col[N];
bool dfs(int x, int c) {
    if(col[x]) {
        return col[x] == c;
    }
    col[x] = c;
    reg(i, x) {
        int y = e[i].to;
        if(!dfs(y, -c))
            return false;
    }
    return true;
}

int a[N];
int b[N];
ll c[N];

Edge ee[M];
int la[N];
int es = 1;

int main()
{
    int n;
    cin >> n;
    rep(i, 1, n) {
        scanf("%d", &a[i]);
    }
    rep(i, 1, n) {
        scanf("%d", &b[i]);
    }
    rep(i, 1, n) {
        scanf("%lld", &c[i]);
    }

    tot = 1;
    memset(last, 0, sizeof(last));

    rep(i, 1, n) {
        if(a[i] == 0) continue;
        Fact(abs(a[i]));
        rep(j, 1, n) {
            if(a[j] == 0) continue;
            if(a[i] % a[j] == 0) {
                int div = a[i] / a[j];
                for(int k = 1; k <= cnt; k++) {
                    if(p[k] == div) {
                        ine2(i, j, 0, 0);
                        //printf("%d %d\n", i, j);
                        break;
                    }
                }
            }
        }
    }

    rep(i, 1, n) {
        if(!col[i]) {
            dfs(i, 1);
        }
    }

    s = n + 1;
    t  = s + 1;

    memcpy(la, last, sizeof(last));
    memcpy(ee, e, sizeof(e));
    es = tot;

    memset(last, 0, sizeof(last));
    memset(e, 0, sizeof(e));
    tot = 1;

    /*for(int i = 1; i <= n; i++) {
        //printf("%d, col: %d\n", i, col[i]);
    }*/

    rep(x, 1, n) {
        if(col[x] == 1) {
            add(s, x, b[x], 0);
            printf("s, %d: %d %lld\n", x, b[x], 0);
            for(int i = la[x]; i; i = ee[i].pre) {
                int y = ee[i].to;
                add(x, y, INF, c[x] * c[y]);
                printf("%d, %d: %d %lld\n", x, y, INF, c[x] * c[y]);
            }
        } else if(col[x] == -1) {
            add(x, t, b[x], 0);
            printf("%d, t,: %d %lld\n", x, b[x], 0);
        }
    }

    MCMF();

    printf("%d\n", maxflow);
}
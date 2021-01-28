#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 2333334;
const int N = 2333333;

struct Edge
{
    int from, to, pre;
    ll w;
} e[M];
int last[M];
int tot = 0;

void ine(int a, int b, ll w)
{
    tot++;
    e[tot].from = a;
    e[tot].to = b;
    e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w)
{
    ine(a, b, w);
    ine(b, a, w);
}

#define reg(i, x) for (int i = last[x]; i; i = e[i].pre)

int n, m, clock, low[N], dfn[N], iscut[N];

// 求桥, 边双ebcc
bool vis[N];
int sta[N], top = 0;
int color[N], ebccnum = 0;
void tarjan(int cur, int dad)
{
    sta[++top] = cur;
    vis[cur] = 0;
    low[cur] = dfn[cur] = ++clock;
    bool flag = false;
    reg(i, cur)
    {
        int nex = e[i].to;
        if(nex == dad && !flag) {   // 这是正常的反向边，不要碰它
            flag = true;
            continue;
        }
        if (!dfn[nex])  // 树边
        {
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        }
        else if (!vis[nex]) // 也是提防重边
        {
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if(dfn[cur] == low[cur]) {  // 从dad到cur是一个桥
        ebccnum++;
        do {
            vis[sta[top]] = 1;
            color[sta[top]] = ebccnum;
        } while(top && sta[top--] != cur);
    }
}


int deg[N]; // 缩点树的度数
void build()
{
    rep(x, 1, n) {
        reg(i, x) {
            if(color[e[i].to] != color[x])
                deg[color[x]]++;
                // 其余操作……
        }
    }
}

int main()
{
    cin >> n >> m;
    int u, v;
    rep(i, 1, m) {
        scanf("%d %d", &u, &v);
        ine2(u, v, 0);
    }

    tarjan(1, 0);
    build();

    int cnt = 0;
    rep(i, 1, ebccnum) {
        if(deg[i] == 1) cnt++;
    }

    cout << (1 + cnt) / 2 << endl;
}
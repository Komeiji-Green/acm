#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 300005, M = 55;
const long long P = 998244353;

int dep[N], n, m, en, h[N], fa[N][20];
long long val[N][55];

struct Edge
{
    int b, next;
} e[N << 1];

void AddEdge(int sa, int sb)
{
    e[++en].b = sb;
    e[en].next = h[sa];
    h[sa] = en;
}

long long QPow(long long x, long long y)
{
    long long ans = 1;
    while (y)
    {
        if (y & 1)
            ans = ans * x % P;
        y >>= 1;
        x = x * x % P;
    }
    return ans;
}

void dfs(int u, int fat)
{
    for (int i = h[u]; i; i = e[i].next)
    {
        int v = e[i].b;
        if (v == fat)
            continue;
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        long long now = dep[v];
        for (int j = 1; j <= 50; j++)
        {
            val[v][j] = (val[u][j] + now) % P;
            //printf("[%d,%d]=%lld\n",v,j,val[v][j]);
            now = (now * dep[v]) % P;
        }
        dfs(v, u);
    }
}

void Calc()
{
    for (register int i = 1; i <= 19; i++)
    {
        for (register int j = 1; j <= n; j++)
        {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
}

int LCA(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    int deep = dep[u] - dep[v];
    for (int i = 0; i <= 19; i++)
        if ((deep >> i) & 1)
            u = fa[u][i];
    for (int i = 19; i >= 0; i--)
    {
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return u == v ? u : fa[u][0];
}

int main()
{
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    scanf("%d", &n);
    dep[1] = 0;
    for (register int i = 1; i <= 50; i++)
        val[1][i] = 0;
    for (register int i = 1; i < n; i++)
    {
        int sa, sb;
        scanf("%d %d", &sa, &sb);
        AddEdge(sa, sb);
        AddEdge(sb, sa);
    }
    scanf("%d", &m);
    dfs(1, 0);
    Calc();
    while (m--)
    {
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        int lca = LCA(i, j);
        //printf("%d %d %d %d\n",i,j,k,lca);
        printf("%lld\n", (val[i][k] + val[j][k] - val[lca][k] * 2 + P * 2 + QPow(dep[lca], k)) % P);
    }
    return 0;
}
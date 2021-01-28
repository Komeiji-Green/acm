#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
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

int n, m, stamp, low[N], dfn[N], iscut[N];
void tarjan(int cur, int dad)
{
    int child = 0;
    low[cur] = dfn[cur] = ++stamp;
    reg(i, cur)
    {
        int nex = e[i].to;
        if (!dfn[nex]) // 树边
        {
            child++;
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
            if (low[cur] >= dfn[cur])
                iscut[cur] = true;
        }
        else if (dfn[nex] < dfn[cur] && nex != dad) // 回边
        {
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if (dad == 0 && child == 1) // 对根情况单独讨论
        iscut[cur] = false;
}

// 求桥, ebcc
bool vis[N];
int sta[1000000], top = 0;
int color[N], ebccnum = 0;
void tarjan(int cur, int dad)
{
    stack[++top] = x;
    vis[x] = 0;
    low[cur] = dfn[cur] = ++stamp;
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
    if(dfn[x] == low[x]) {  // 从dad到cur是一个桥
        ebccnum++;
        do {
            vis[sta[top]] = 1;
            color[sta[top]] = ebccnum;
        } while(top && sta[top--] != x);
    }
}

int head[N], dfn[N], dfs_clock, tot;
int num;           //bcc数量
int stack[N], top; //栈
vector<int> bcc[N];
int tarjan(int u, int fa)
{
    int lowu = dfn[u] = ++dfs_clock;
    reg(i, u)
    {
        int y = e[i].to;
        if (!dfn[y])
        {
            stack[++top] = y; //搜索到的点入栈
            int lowv = tarjan(y, u);
            lowu = min(lowu, lowv);
            if (lowv >= dfn[u]) //是割点或根
            {
                num++;
                while (stack[top] != y)
                    bcc[num].push_back(stack[top--]);
                bcc[num].push_back(stack[top--]); // y及y的子树出栈
                bcc[num].push_back(u);            // 割点存入bcc但不出栈
            }
        }
        else if (y != fa)
            lowu = min(lowu, dfn[y]);
    }
    return lowu;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    for (int i = 1; i <= n; i++) //遍历n个点tarjan
        if (!dfn[i])
        {
            stack[top = 1] = i;
            tarjan(i, i);
        }
    for (int i = 1; i <= num; i++)
    {
        printf("BCC#%d: ", i);
        for (int j = 0; j < bcc[i].size(); j++)
            printf("%d ", bcc[i][j]);
        printf("\n");
    }
    return 0;
}
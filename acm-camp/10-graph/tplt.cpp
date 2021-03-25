#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
const int N = 2333333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[N], tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

// euler 优化版
bool vis[M];    // 对于边的vis数组
int stk[M][2], top = 0;    // 用于存放欧拉路径
void euler(int x) {
    int cnt = 0;
    reg(i, x) { 
        //int y = e[i].to;
        if(vis[i] || vis[i ^ 1]) continue;
        if (cnt == 0) last[x] = i;
        cnt++;
        vis[i] = vis[i ^ 1] = 1;
        euler(e[i].to);
        stk[top][0] = x;
        stk[top][1] = e[i].to;
        top++;
        i = last[x];
    }
}

// spfa
bool inq[N];
int Q[N], dis[N], nums[N]; // nums: 入队次数，判负边
bool spfa(int n) {
    int head = 0, tail = 1;
    memset(nums, 0, sizeof(nums));
    rep(i, 1, n) {
        inq[i] = true;
        Q[tail++] = i;  // 考虑到非连通性
        nums[i]++;
        dis[i] = 0;     // 判负边用0，求最短路用INF
    }
    while(head <= tail) {
        int x = Q[head++];
        inq[x] = false;
        reg(i, x) {
            int y = e[i].to;
            if(dis[y] > e[i].w + dis[x]) {
                dis[y] = e[i].w + dis[x];
                if(!inq[y]) {
                    inq[y] = true;
                    Q[tail++] = y;
                    nums[i]++;
                    if(nums[i] >= n) return true;   // 如果n次入队，则有负圈
                }
            }
        }
    }
    return false;
}

// dijkstra
ll dis[N];
bool vis[N];
void dijkstra(int s) {
    priority_queue<pair<ll, int> > q;
    q.push(mp(0, s));
    while(!q.empty()) {
        int u = q.top().second; 
        ll w = -q.top().first;
        q.pop();
        if(vis[u]) continue;
        vis[u] = true; dis[u] = w;
        reg(i, u) {
            if(vis[e[i].to]) continue;
            q.push(mp(-(e[i].w + w), e[i].to));
        }
    }
}

// 并查集
int f[N];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    f[fx] = fy;
}

// Kruskal
struct cmp {
    bool operator() (const Edge&lhs, const Edge& rhs) {
        return lhs.w > rhs.w;
    }
};
ll Kruskal(int n) { // 最大权生成树
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

const ll INF = 2147483647;
const int maxn = 100 + 5;
ll G[maxn][maxn], dis[maxn][maxn]; 
int floyd(int n) {
    rep(i, 1, n) rep(j, 1, n) dis[i][j] = G[i][j]; // 默认inf, 到自身为0
    ll minCircle = INF;
    rep(k, 1, n) {
        rep(i, 1, k - 1)
            rep(j, 1, k - 1) {  // 此时dis[i][j]表示的路径只经过[1, k - 1]
                if(G[i][k] == 0 || G[k][j] == 0) continue;
                minCircle = min(minCircle, G[i][k] + G[k][j] + dis[i][j]);
            }
        rep(i, 1, n)
            rep(j, 1, n) {
                //if(i == j || i == k || k == j) continue;  // 可加可不加
                //if(dis[i][j] == -1) dis[i][j] = dis[i][k] + dis[k][j];
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
    }
    return minCircle;
}


int clock, low[N], dfn[N], iscut[N];
// 求桥, ebcc
bool vis[N];
int sta[1000000], top = 0;
int ebcc[N], ebccnum = 0;
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
        if (!dfn[nex]) { // 树边
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        }
        else if (!vis[nex]) { // 防重边
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if(dfn[cur] == low[cur]) {  // 从dad到cur是一个桥
        ebccnum++;
        //printf("%d: ", ebccnum);
        do {
            vis[sta[top]] = 1;
            ebcc[sta[top]] = ebccnum;
            //printf("%d ", sta[top]);
        } while(top && sta[top--] != cur);
        //printf("\n");
    }
}

// 强连通分量
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
int nums[N], minv[N], cost[N]; // 结点数、最小权
void tarjan(int cur, int dad)
{
    sta[++top] = cur;
    vis[cur] = 0;
    dfn[cur] = ++clock;
    low[cur] = clock;
    //bool flag = false;
    reg(i, cur)
    {
        //flag = true;
        int nex = e[i].to;
        if (!dfn[nex]) { // 树边
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        }
        else if (!vis[nex]) { // 非横边
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if((dfn[cur] == low[cur]) /*|| (dad == 0 && !flag)*/) { 
        sccnum++;
        minv[sccnum] = mod;
        nums[sccnum] = 1;
        do {
            vis[sta[top]] = 1;
            scc[sta[top]] = sccnum;
            int &mm = minv[sccnum];
            int &cc = cost[sta[top]];
            if(mm == cc) nums[sccnum]++;
            else if(cc < mm) { 
                mm = cc;
                nums[sccnum] = 1;
            }
        } while(top && sta[top--] != cur);
    }
}

// bcc

// 匈牙利算法：先用G存，注意重边
int l, r, m;    // 左、右、边

int linker[N];
bool vis[N];
bool dfs(int x) {
    reg(i, x) {
        int y = e[i].to;
        if(vis[y]) continue;
        vis[y] = true;
        if(!linker[y] || dfs(linker[y])) {
            linker[y] = x;
            return true;
        }
    }
    return false;
}

int Hungarian() {
    int ans = 0;
    memset(linker, 0, sizeof(linker));
    rep(i, 1, l) {
        memset(vis, 0, sizeof(vis));
        if(dfs(i))
            ans++;
    }
    return ans;
}

// 最大权二分匹配：使用前需init,匹配情况记录在linker中
// const int N = 305;
int lx[N], ly[N], slack[N], visx[N], visy[N], linker[N];
int G[N][N];
int nx, ny;

bool dfs(int x) {
    visx[x] = true;
    int tempDelta;
    rep(y, 1, ny) {
        if(visy[y]) continue;
        tempDelta = lx[x] + ly[y] - G[x][y];
        if(tempDelta == 0) {
            visy[y] = true;  
            if(!linker[y] || dfs(linker[y])) {
                linker[y] = x;
                return true;
            }
        } else if(slack[y] > tempDelta)
                slack[y] = tempDelta;
    }
    return false;
}
void KM() {
    rep(x, 1, nx) {
        rep(j, 1, ny) slack[j] = INF;
        while(true) {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if(dfs(x)) break;
            else {
                int delta = INF;
                rep(j, 1, ny) 
                    if(!visy[j] && slack[j] < delta) 
                        delta = slack[j];
                rep(i, 1, nx)
                    if(visx[i]) 
                        lx[i] -= delta;
                rep(j, 1, ny)
                    if(visy[j])
                        ly[j] += delta;
                    else 
                        slack[j] -= delta;
            }
        }
    }
}
void init() {
    memset(linker, 0, sizeof(linker));
    memset(ly, 0, sizeof(ly));
    rep(i, 1, nx) {
        int temp = 0;
        rep(j, 1, ny) {
            if(G[i][j] > temp) temp = G[i][j];
        }
        lx[i] = temp;
    }
}

int size[N]; // 子树大小
int dep[N]; // 深度
int anc[N][30]; // 祖先
int minv[N][30]; // 最小权
int lg;

// dad是用来防止重复遍历的
void change(int x, int dad, int dept) {
    size[x] = 1;
    dep[x] = dept;
    for(lg = 0; lg <= 20; lg++) if(n < (1 << (lg - 1))) break;
    rep(i, 1, lg) {
        if(dep[x] < (1 << i)) break;
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
        minv[x][i] = min(minv[x][i - 1], minv[anc[x][i - 1]][i - 1]);
    }
    for(int i = la[x]; i; i = ee[i].pre) {
        int y = ee[i].to;
        if(y == dad) continue;
        anc[y][0] = x;
        minv[y][0] = ee[i].w;
        change(y, x, dept + 1);
        size[x] += size[y];
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

int query_min(int a, int b) {
    for(lg = 1; lg <= 20; lg++) if((1 << (lg - 1)) > n) break;
    if(dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b], ret = INF;
    for(int i = lg; i >= 0; i--) {
        if(dep[a] < (1 << i)) continue;
        if((1 << i) & d) { 
            ret = min(ret, minv[a][i]);
            a = anc[a][i];
        }
    }
    if(a == b) return ret;
    for(int i = lg; i >= 0; i--) {
        if(dep[a] < (1 << i)) continue;
        if(anc[a][i] != anc[b][i]) {
            ret = min(ret, min(minv[a][i], minv[b][i]));
            a = anc[a][i]; b = anc[b][i];
        }
    }
    if(a != b) {
        ret = min(ret, min(minv[a][0], minv[b][0]));
        a = anc[a][0]; b = anc[b][0];
    }
    return ret;
}
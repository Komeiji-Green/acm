#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int M = 23333, N = 23333;
const int maxk = 10000005;

struct Edge {
    int from, to, pre, w;
} e[M];
int last[N], tot;
void ine(int a, int b, int w) {
    ++tot;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, int w) { ine(a, b, w); ine(b, a, w); }
#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

// 点分治
int sz[N], maxx[N];
bool vis[N];

int rt;     // 重心，初始为0，且maxx[0] = inf;
int sum;    // 待求重心的子树的大小
void calcsz(int x, int dad) {
    maxx[x] = 0; sz[x] = 1;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad || vis[y]) continue;
        calcsz(y, x);
        sz[x] += sz[y]; maxx[x] = max(sz[y], maxx[x]);
    }
    maxx[x] = max(maxx[x], sum - sz[x]);
    if(maxx[x] < maxx[rt]) rt = x;
}

// -------1
bool ans[550]; int k[550], m;
int len[N];
bool inq[maxk];      // 已有的路径长度
queue<int> qa, qb;   // qa用来加入待加队列，qb用来清空
void calclen(int x, int dad) {
    for(int i = 1; i <= m; ++i)
        if(len[x] <= k[i] && inq[k[i]-len[x]]) ans[i] = true;
    qa.push(len[x]);
    reg(i, x) {
        int y = e[i].to;
        if(y == dad || vis[y]) continue;
        len[y] = e[i].w + len[x]; calclen(y, x);
    }
}
// 1-------

void dfz(int x) {
    calcsz(x, 0); vis[rt] = true; // rt: 重心
    //printf("%d\n", rt);

    // -------1
    len[rt] = 0;
    reg(i, rt) {
        int y = e[i].to; if(vis[y]) continue;
        len[y] = e[i].w; calclen(y, rt);
        while(!qa.empty()) {
            int uu = qa.front(); qa.pop();
            if(uu < maxk) { inq[uu] = true; qb.push(uu); }
        }
    }
    for(int i = 1; i <= m; ++i) if(inq[k[i]]) ans[i] = true;
    while(!qb.empty()) {
        int uu = qb.front(); qb.pop();
        inq[uu] = false;
    }
    // 1--------

    int tmp = rt;
    reg(i, tmp) {
        int y = e[i].to; if(vis[y]) continue;
        sum = sz[y]; rt = tmp; dfz(y); // ！一定要在调用前设置全部变量设置成正确的值
    }
}

int main() {
    int n;
    cin >> n >> m;
    int u, v, w;
    for(int i = 2; i <= n; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        ine2(u, v, w);
    }
    for(int i = 1; i <= m; ++i) scanf("%d", &k[i]);

    rt = 0; maxx[rt] = inf; sum = n; dfz(1); // 调用点分治 

    for(int i = 1; i <= m; ++i) {
        if(ans[i]) printf("AYE\n");
        else printf("NAY\n");
    }
}
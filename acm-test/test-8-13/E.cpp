#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int M = 42333;
const int N = 500;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[N];
Edge temp_e[M];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) {
    ine(a, b, w); ine(b, a, w);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

// 最大流
int n, num, m, s, t, lv[N], cur[N];  // lv：每点层数，cur：当前弧
inline bool bfs() 
{
    rep(i, 1, n) lv[i] = -1;
    lv[s] = 0;
    memcpy(cur, last, sizeof(last));
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = cur[u]; i; i = e[i].pre) {
            int to = e[i].to;
            ll vol = e[i].w;
            if(vol > 0 && lv[to] == -1)
                lv[to] = lv[u] + 1, q.push(to);
        }
    }
    return lv[t] != -1; // 如果汇点未访问过则不可达
}

ll dfs(int u = s, ll f = INF) {
    if(u == t) 
        return f;
    for(int &i = cur[u]; i; i = e[i].pre) {
        int to = e[i].to;
        ll vol = e[i].w;
        if(vol > 0 && lv[to] == lv[u] + 1) {
            ll c = dfs(to, min(vol, f));
            if(c) {
                e[i].w -= c;
                e[i ^ 1].w += c;    // 反向边
                return c;
            }
        }
    }
    return 0; // 输出流量大小
}

inline ll dinic()
{
    ll ans = 0;
    while(bfs()) {
        ll f;
        while((f = dfs()) > 0) {
            ans += f;
            //printf("%d\n", ans);
        }
    }
    return ans;
}

int f1[N];//, f2[N];
int find1(int x) { return f1[x] == x ? x : (f1[x] = find1(f1[x])); }
//int find2(int x) { return f2[x] == x ? x : (f2[x] = find2(f2[x])); }
void merge1(int x, int y) {
    int fx = find1(x);
    int fy = find1(y);
    f1[fx] = fy;
}
/*void merge2(int x, int y) {
    int fx = find2(x);
    int fy = find2(y);
    f2[fx] = fy;
}*/

bool G[N][N];
bool GG[N][N];

bool check(int x) {
    memcpy(e, temp_e, sizeof(temp_e));
    reg(i, s) {
        e[i].w = x;
    }
    rep(i, num + 1, 2 * num) {
        reg(j, i) {
            if(e[j].to == t)
                e[j].w = x; // 不要去整反向边！！
        }
    }
    //printf("%d\n", x);
    ll ans = dinic();
    if(ans == 1ll * num * x) return true;
    else return false;
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int f;
        cin >> num >> m >> f;

        memset(G, 0, sizeof(G));
        memset(GG, 0, sizeof(GG));
        rep(i, 1, num) f1[i] = i;
        //rep(i, 1, num) f2[i] = i;
        int u, v;
        rep(i, 1, m) {
            scanf("%d %d", &u, &v);
            G[u][v] = true;
        }
        rep(i, 1, f) {
            scanf("%d %d", &u, &v);
            merge1(u, v);
        }
        rep(i, 1, num) {
            int fi = find1(i);
            rep(j, 1, num) {
                if(G[i][j]) GG[fi][j] = true;
            }
        }

        tot = 1;
        memset(last, 0, sizeof(last));

        rep(i, 1, num) {
            int fi = find1(i);
            rep(j, 1, num) {
                if(GG[fi][j]) {
                    ine(i, num + j, 1);
                    ine(num + j, i, 0);
                }
            }
        }

        //printf("1\n");

        s = 2 * num + 1;
        t = 2 * num + 2;
        n = t;
        rep(i, 1, num) {
            ine(s, i, 0);
            ine(i, s, 0);
        }
        rep(j, num + 1, 2 * num) {
            ine(j, t, 0);
            ine(t, j, 0);
        }

        memcpy(temp_e, e, sizeof(e));

        int le = 0, ri = 100;
        int mid = (le + ri + 1) >> 1;
        while(le < ri) {
            if(check(mid)) {
                le = mid;
            } else {
                ri = mid - 1;
            }
            mid = (le + ri + 1) >> 1;
        }
        printf("%d\n", mid);
    }
}
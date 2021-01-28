#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair
#define P pair<int, int>

typedef long long ll;
const int INF = 0x3f3f3f3f;
const int M = 833333;
const int N = 90000;

struct Edge {
    int from, to, pre;
    int w;
} e[M];
int last[N];
//Edge temp_e[M];
int tot = 1;

void ine(int a, int b, int w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
void add(int a, int b, int w) {
    ine(a, b, w);
    ine(b, a, 0);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

// 最大流
int s, t, lv[N], cur[N];  // lv：每点层数，cur：当前弧
inline bool bfs(int n) 
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
            int vol = e[i].w;
            if(vol > 0 && lv[to] == -1)
                lv[to] = lv[u] + 1, q.push(to);
        }
    }
    return lv[t] != -1; // 如果汇点未访问过则不可达
}

int dfs(int u = s, int f = INF) {
    if(u == t) 
        return f;
    for(int &i = cur[u]; i; i = e[i].pre) {
        int to = e[i].to;
        int vol = e[i].w;
        if(vol > 0 && lv[to] == lv[u] + 1) {
            int c = dfs(to, min(vol, f));
            if(c) {
                e[i].w -= c;
                e[i ^ 1].w += c;    // 反向边
                return c;
            }
        }
    }
    return 0; // 输出流量大小
}

int dinic(int n)
{
    int ans = 0;
    while(bfs(n)) {
        int f;
        while((f = dfs()) > 0) {
            ans += f;
            //printf("%d\n", ans);
        }
    }
    return ans;
}

int n;

int G[205][205];
bool B[205][205];
int nei[8][2] = { {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1} };

bool in(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n && !B[i][j];
}

int main()
{
    cin >> n;

    int m;
    cin >> m;
    int x, y;

    int cnt = 0;
    for(int i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        if(!B[x][y]) cnt++;
        B[x][y] = true;
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            G[i][j] = (i - 1) * n + j;

    tot = 1;
    memset(last, 0, sizeof(last));
    s = n * n + 1;
    t = s + 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(!in(i, j)) continue;
            if((i + j) & 1) {
                add(s, G[i][j], 1);
                for(int k = 0; k < 8; k++) {
                    int ii = i + nei[k][0];
                    int jj = j + nei[k][1];
                    if(in(ii, jj)) {
                        add(G[i][j], G[ii][jj], INF);
                    }
                }
            } else {
                add(G[i][j], t, 1);
            }
        }
    }

    int ans = dinic(t);
    printf("%d\n", n * n - cnt - ans);
}
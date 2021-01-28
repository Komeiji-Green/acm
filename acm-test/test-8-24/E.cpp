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
const int M = 533333;
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
inline bool bfs() 
{
    //printf("%d\n", n);
    memset(lv, 0, sizeof(lv));
    //rep(i, 1, n) lv[i] = -1;
    lv[s] = 1;
    memcpy(cur, last, sizeof(last));
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = cur[u]; i; i = e[i].pre) {
            int to = e[i].to;
            int vol = e[i].w;
            if(vol > 0 && !lv[to]) {
                lv[to] = lv[u] + 1, q.push(to);
                //printf("%d %d %d\n", u, to, lv[to]);
            }
        }
    }
    return lv[t] != 0; // 如果汇点未访问过则不可达
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

int dinic()
{
    int ans = 0;
    while(bfs()) {
        //printf("kkksc\n");
        int f;
        while((f = dfs()) > 0) {
            ans += f;
            //printf("%d\n", ans);
        }
    }
    return ans;
}

int H[N];
vector<int> S[N];

int pos(int x, int t, int n) {
    return x == -1 ? 1 : (x + 3) + t * (n + 2);
}

bool check(int T, int n, int m, int k) {
    tot = 1;
    memset(last, 0, sizeof(last));
    //memset(e, 0, sizeof(e));

    //printf("%d\n", T);

    rep(i, 1, m) {
        int sz = S[i].size();
        for(int j = 0, x, y; j < T; j++) {
            x = S[i][j % sz], y = S[i][(j + 1) % sz];
            if(x != -1) {
                add(pos(x, j, n), pos(y, j + 1, n), H[i]);
                //if(y == -1) printf("haoye\n");
            }
        }
    }

    rep(i, 0, n) {
        rep(j, 0, T - 1) {
            add(pos(i, j, n), pos(i, j + 1, n), INF);
        }
    }

    s = 2; t = 1;
    add(s, pos(0, 0, n), k);
    int ans = dinic();
    //printf("%d\n", ans);
    if(ans >= k) {
        return true;
    } else return false;
}

int main()
{   
    int n, m, k;
    cin >> n >> m >> k;
    int r;
    rep(i, 1, m) {
        scanf("%d %d", &H[i], &r);
        int x;
        rep(j, 1, r) {
            scanf("%d", &x);
            S[i].push_back(x);
        }
    }

    int MAX = (n + 2) * (n + 2) * (k + 1) + 1;
    int le = 0, ri = MAX;
    int mid = (le + ri) >> 1;
    while(le < ri) {
        //printf("1\n");
        if(check(mid, n, m, k)) {
            ri = mid;
        } else {
            le = mid + 1;
        }
        mid = (le + ri) >> 1;
    }

    if(mid == MAX) printf("0\n");
    else printf("%d\n", mid);
}
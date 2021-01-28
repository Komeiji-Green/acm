#include <iostream>
#include <queue>
#include <cstring>
#include <stack>
using namespace std;

#define mian main
#define sizoef sizeof
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int N = 233333, M = 466666;

struct Node {
    Node() {}
    Node(int _x, int _d): x(_x), d(_d) {}
    int x, d;
};

struct Edge {
    Node from, to;
    int pre;
    int w;
} e[M];
struct Edge2 {
    int from, to, pre, w;
} ee[M];
int last[N][2], la[N];
int tot = 0, es = 0;

int deg[N];  // 出度

void ine(Node a, Node b, int w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a.x][a.d];
    last[a.x][a.d] = tot;
    deg[a.x]++;
}

int indeg[N];  // 入度

void ine2(int a, int b, int w) {
    es++;
    ee[es].from = a; ee[es].to = b; ee[es].w = w;
    ee[es].pre = la[a];
    la[a] = es;
    //indeg[b]++;
}

#define reg(i, v) for(int i = last[v.x][v.d]; i; i = e[i].pre)
#define rreg(i, x) for(int i = la[x]; i; i = ee[i].pre)

Node s, t; // 终点

bool checkcircle(int n) {
    queue<int> q;
    queue<int> qq;

    bool vis[N] = {};
    qq.push(s.x);
    while(!qq.empty()) {
        int u = qq.front(); qq.pop();
        if(vis[u]) continue;
        vis[u] = true;
        rreg(i, u) {
            int v = ee[i].to;
            qq.push(v);
        }
    }

    rep(x, 1, n) rreg(i, x) {
        int y = ee[i].to;
        if(vis[x] && vis[y]) indeg[y]++;
    }

    rep(x, 1, n) {
        if(vis[x] && indeg[x] == 0) q.push(x);
    }

    int cnt = 0;
    while(!q.empty()) {
        int x = q.front(); q.pop();
        cnt++;
        rreg(i, x) {
            int y = ee[i].to;
            indeg[y]--;
            if(indeg[y] == 0) q.push(y);
        }
    }

    rep(i, 1, n) {
        if(vis[i]) cnt--;
    }
    if(cnt == 0) return false;
    else return true;
}

Node fa[N][2];

bool bfs() {
    bool vis[N][2] = {};
    queue<Node> q;
    q.push(s);

    while(!q.empty()) {
        Node u = q.front(); q.pop();
        if(vis[u.x][u.d]) continue;
        vis[u.x][u.d] = true;
        reg(i, u) {
            Node v = e[i].to;
            if(!vis[v.x][v.d]) {
                q.push(v);
                fa[v.x][v.d] = u;
                if(deg[v.x] == 0 && v.d == 1) {
                    t = v;
                    return 1;
                }
            }
        }
    }
    return 0;
}


int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    rep(x, 1, n) {
        int dg, y;
        scanf("%d", &dg);
        rep(j, 1, dg) {
            scanf("%d", &y);
            ine(Node(x, 0), Node(y, 1), 0);
            ine(Node(x, 1), Node(y, 0), 0);
            ine2(x, y, 0);
        }
    }

    int sx;
    scanf("%d", &sx);
    s = Node(sx, 0);

    bool ans = bfs();
    if(ans) {
        stack<int> ret;
        ret.push(t.x);
        for(Node cur = t; cur.x != s.x || cur.d != s.d; cur = fa[cur.x][cur.d]) {
            Node f = fa[cur.x][cur.d];
            ret.push(f.x);
        }
        printf("Win\n");
        while(!ret.empty()) {
            printf("%d ", ret.top());
            ret.pop();
        }
        printf("\n");
    } else {
        if(checkcircle(n)) {
            printf("Draw\n");
        } else {
            printf("Lose\n");
        }
    }
}
// topo sorting

#include <iostream>
#include <queue>
#include <cstring>
#include <queue>
#include <cstdio>

using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair
#define P pair<int, int>

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int M = 1000500;
const int N = 1060;

struct Edge {
    int from, to, pre;
    int w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, int w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, int w) {
    ine(a, b, w); ine(b, a, w);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int a[N];   
int deg[N];
int n;

void topo() {
    queue<int> q;   // 入度为0的结点

    int cnt = 0;    // 遍历点的数量
    memset(deg, 0, sizeof(deg));
    rep(x, 1, n) {
        reg(i, x) deg[e[i].to]++;
    }
    rep(i, 1, n) if(deg[i] == 0) q.push(i);
    while(!q.empty()) {
        cnt++;
        int cur = q.front(); q.pop();
        a[cnt] = cur;
        reg(i, cur) {
            int y = e[i].to;
            deg[y]--;
            if(deg[y] == 0)
                q.push(y);
        }
    }
}

int sg[N];
void DP() {
    memset(sg, 0, sizeof(sg));
    //memset(a, 0, sizeof(a));
    bool vis[N];
    for(int x = n; x >= 1; x--) {
        memset(vis, 0, sizeof(vis));
        reg(i, a[x]) {
            int y = e[i].to;
            vis[sg[y]] = true;
        }
        for(int i = 0; i < N; i++) {
            if(!vis[i]) {
                sg[a[x]] = i;
                break;
            }
        }
    }
}

int main()
{
    while(scanf("%d", &n) != EOF) {

        tot = 0;
        memset(last, 0, sizeof(last));
        int num, y;
        rep(i, 1, n) {
            scanf("%d", &num);
            rep(j, 1, num) {
                scanf("%d", &y);
                ine(i, y + 1, 0);
            }
        }

        topo();
        DP();

        int m;
        while(scanf("%d", &m) != EOF && m) {
            int ans = 0, pos;
            rep(i, 1, m) {
                scanf("%d", &pos);
                ans ^= sg[pos + 1];
            }
            if(ans) {
                printf("WIN\n");
            } else {
                printf("LOSE\n");
            }
        }
    }
}
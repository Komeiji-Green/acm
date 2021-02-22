#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)

typedef long long ll;

const int M = 20405000;
const int N = 10205000;

struct Edge {
    int to, pre;
    int w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, int w) {
    tot++;
    e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, int w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int dis[N];
bool vis[N];
void dijkstra(int s) {
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, s));
    while(!q.empty()) {
        int u = q.top().second; 
        int w = -q.top().first;
        q.pop();
        if(vis[u]) continue;
        vis[u] = true; dis[u] = w;
        reg(i, u) {
            if(vis[e[i].to]) continue;
            q.push(make_pair(-(e[i].w + w), e[i].to));
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    int u, v, w;
    while(m--) {
        scanf("%d %d %d", &u, &v, &w);
        int x = u, y = n * w + v;
        ine(x, y, w * w);
        x = v, y = n * w + u;
        ine(x, y, w * w);
        for(int h = 1; h <= 50; ++h) {
            x = u; y = n * h + v;
            ine(y, x, w * w + 2 * h * w);
        }
        for(int h = 1; h <= 50; ++h) {
            x = v; y = n * h + u;
            ine(y, x, w * w + 2 * h * w);
        }
    }
    dijkstra(1);
    for(int i = 1; i <= n; ++i) {
        if(!vis[i]) {
            printf("-1 ");
        } else {
            printf("%d ", dis[i]);
        }
    }
    printf("\n");
}
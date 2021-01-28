#include <iostream>
#include <queue>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
const int N = 233333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[M];
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

int n, m;
int main()
{
    cin >> n >> m;
    int u, v;
    ll w;
    rep(i, 1, m) {
        scanf("%d%d%lld", &u,&v,&w);
        ine2(u, v, 2 * w);
    }

    // 点权化边权
    int s = n + 1;
    rep(i, 1, n) {
        scanf("%lld", &w);
        ine2(i, s, w);
    }

    // 转化为单源最短路问题
    dijkstra(s);
    
    rep(i, 1, n) {
        printf("%lld ", dis[i]);
    }
    printf("\n");
}
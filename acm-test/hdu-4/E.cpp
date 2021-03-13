#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;

const int M = 4333333;
const int N = 233333;

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
void init(int n) {
    int nn = 2 * n + 1;
    for(int i = 1; i <= nn; ++i) dis[i] = INF, vis[i] = 0;
}

char tag[N];

int main() {
    int T, n, m, s, t, u, v;
    ll x, w;
    cin >> T;
    while(T--) {
        scanf("%d %d %d %d %lld", &n, &m, &s, &t, &x);
        scanf("%s", tag + 1);
        int nn = 2 * n + 1;
        tot = 0; for(int i = 1; i <= nn; ++i) last[i] = 0; 
        while(m--) {
            scanf("%d %d %lld", &u, &v, &w);
            for(int i = 0; i <= 1; ++i) {
                if(!(tag[u]=='M' || tag[u]=='L'&&i==0 || tag[u]=='R'&&i==1)) continue;
                for(int j = 0; j <= 1; ++j) {
                    if(!(tag[v]=='M' || tag[v]=='L'&&j==0 || tag[v]=='R'&&j==1)) continue;
                    ine2(2*u+i, 2*v+j, w + (i==j ? 0 : x));
                }
            }
        }
        for(int i = 1; i <= n; ++i) {
            if(tag[u] == 'M') ine2(2*u, 2*u+1, x);
        }
        ll ans = INF;
        init(n);
        dijkstra(2*s);
        ans = min(ans, min(dis[2*t], dis[2*t+1]));
        init(n);
        dijkstra(2*s+1);
        ans = min(ans, min(dis[2*t], dis[2*t+1]));
        printf("%lld\n" ,ans);
    }
}
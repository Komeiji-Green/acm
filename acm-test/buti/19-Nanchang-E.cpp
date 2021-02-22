#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 1000007;
const int N = 50007;

struct Edge {
    int from, to, pre, c;
    ll w;
    bool operator< (const Edge& rhs) const {
        return w > rhs.w;
    }
} e[M];
int last[N], tot;

void ine(int a, int b, ll w, int c) {
    ++tot;
    e[tot].from = a; e[tot].to = b; e[tot].w = w; e[tot].c = c;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w, int c) { ine(a, b, w, c); ine(b, a, w, c); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int f[N];
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    f[fx] = fy;
}

int main() {
    int T, n, m, k, u, v, c;
    ll w;
    cin >> T;
    while(T--) {
        cin >> n >> m >> k;
        tot = 0;
        for(int i = 0; i <= n; ++i) last[i] = 0;
        for(int i = 1; i <= n; ++i) f[i] = i;
        ll ans = 0; // 白边
        while(m--) {
            scanf("%d %d %lld %d", &u, &v, &w, &c);
            if(c == 1) {
                ine(u, v, w, c);
            } else {
                merge(u, v);
                ans += w;
            }
        }
        int s = 0; // 连通分量
        for(int i = 1; i <= n; ++i) {
            if(f[i] == i) ++s;
        }
        if(s - 1 > k) {
            ans = -1;
        } else {
            sort(e + 1, e + tot + 1);
            for(int i = 1; i <= tot; ++i) {
                int u = e[i].from, v = e[i].to;
                int fx = find(u), fy = find(v);
                if(fx == fy) continue;
                --k; --s;
                f[fx] = fy;
                e[i].c = 0;
                ans += e[i].w;
            }
            if(s > 1) ans = -1;
            else {
                for(int i = 1; i <= tot && k; ++i) {
                    if(e[i].c == 1) ans += e[i].w, --k;
                }
            }
        }
        printf("%lld\n", ans);
    }
}
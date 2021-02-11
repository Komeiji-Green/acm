#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); ++i)

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
const int M = 8333333;
const int N = 52500;
// 最小费用流

struct Edge {
    int from, to, w, pre;
    ll c;
} e[M];
int last[N];

int tot = 1;
inline void ine(int from, int to, int w, ll c)
{
    e[++tot].to = to;
    e[tot].w = w;
    e[tot].c = c;
    e[tot].from = from;
    e[tot].pre = last[from];
    last[from] = tot;
}

inline void add(int a, int b, int w, ll c) {
    ine(a, b, w, c);
    ine(b, a, 0, -c);
}


int s, t;
int fa[N], flow[N], inq[N]; ll dis[N];
queue<int> Q;
bool SPFA(int n)
{
    while (!Q.empty()) Q.pop();
    for(int i = 1; i <= n; ++i) fa[i] = 0, inq[i] = 0, flow[i] = inf, dis[i] = INF;
    dis[s] = 0; Q.push(s); inq[s] = 1;
    while (!Q.empty())
    {
        int p = Q.front(); Q.pop();
        inq[p] = 0;
        for (int eg = last[p]; eg; eg = e[eg].pre)
        {
            int to = e[eg].to, vol = e[eg].w;
            if (vol > 0 && dis[to] > dis[p] + e[eg].c) // 容量大于0才增广
            {
                fa[to] = eg; // 记录上一条边
                flow[to] = min(flow[p], vol); // 更新下一个点的流量
                dis[to] = dis[p] + e[eg].c; 
                if (!inq[to])
                {
                    Q.push(to);
                    inq[to] = 1;
                }
            }
        }
    }
    return fa[t] != 0;
}
void update() {
    for (int i = t; i != s; i = e[fa[i] ^ 1].to) {
        e[fa[i]].w -= flow[t];
        e[fa[i] ^ 1].w += flow[t];
    }
}


ll a[55], b[55], c[55], pos[55];

struct node {
    int id; ll pos;
    bool operator<(const node& b) {
        return pos < b.pos;
    }
} v[55];
int li[10005], num;
int wh[55][55];
ll func(int i, ll x) {
    return a[i] * x * x + b[i] * x + c[i];
}
int main() {
    int T, n, m;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i =1 ; i<=n;++i) scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
        for(int i = 1; i <= n; ++i) {
            pos[i] = -b[i] / (2 * a[i]);
            if(pos[i] <= 0) pos[i] = 1;
            if(pos[i] > m) pos[i] = m;
            v[i].id = i; v[i].pos = pos[i];
        }
        sort(v + 1, v + n + 1);
        num = 0;
        for(int i = 1, cnt = 0; i <= n; ++i) {
            ++cnt;
            if(i == n || v[i].pos != v[i + 1].pos) {
                int p = v[i].pos;
                for(int k = 0; k < n; ++k) {
                    if(p-k>0 && p-k <= m) li[++num]=(p-k);
                }
                for(int k = 1; k <= n; ++k) {
                    if(p+k>0 && p+k <= m) li[++num]=(p+k);
                }
                cnt = 0;
            }
        }
        for(int i = 1; i <= n; ++i) {
            int l = pos[i], r = pos[i]+1;
            for(int j = 1; j <= n; ++j) {
                if(l <= 0) {
                    li[++num] = r; r++;
                } else if(r > m) {
                    li[++num] = l; l--;
                } else if(func(i, l) < func(i, r)) {
                    li[++num] = l; l--;
                } else {
                    li[++num] = r; r++;
                }
                wh[i][j] = li[num];
            }
        }
        num = 0;
        map<int, int> mp;
        for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) {
            if(!mp.count(wh[i][j])) {
                li[++num] = wh[i][j];
                mp[wh[i][j]] = num;
            }
        }
    
        s = n + num + 1; t = s + 1; 
        int sz = t;

        tot = 1; 
        for(int i = 0; i <= sz; ++i) last[i] = 0;

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                int id = mp[wh[i][j]];
                ll cos = func(i, wh[i][j]);
                add(i, n + id, 1, cos);
            }
        }

        for(int i = 1; i <= n; ++i) {
            add(s, i, 1, 0);
        }
        for(int i = 1; i <= num; ++i) {
            add(n + i, t, 1, 0);
        }
        ll mincost=0;
        for(int i = 1; i <= n; ++i) {
            SPFA(sz);
            mincost += dis[t] * flow[t];
            update();
            printf("%lld", mincost);
            if(i < n) printf(" ");
        }
        printf("\n");
    }
}
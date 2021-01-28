#include<bits/stdc++.h>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;

const int N = 100050, M = 200050;


const int maxn = 100050;
const int sq = 452;
// 对于重点，我们维护长度为1e5的cnt数组，另外维护一个树状数组记录本质不同的出现次数
// 对于轻点，主要在查询上把它的信息传给它的邻居们

vector<int> G[maxn];

bool tmp[sq + 10];
vector<int> hb[sq];
int vis[sq][maxn], C[sq][maxn], n, uu;
int rk[maxn]; // id --> rk
struct Point {
    int deg, val, id;
    bool operator<(const Point& b) {
        return deg > b.deg;
    }
    bool operator==(const Point& b) {
        return deg == b.deg;
    }
} v[maxn];
pair<int, int> inp[maxn];

inline void add(int p, int x, int v) {
    for(register int i = x; i <= n; i += i & (-i)) {
        C[p][i] += v;
    }
}
inline int query(int p, int x) {
    int ans = 0;
    for(register int i = x; i; i -= i & (-i)) {
        ans += C[p][i];
    }
    return ans;
}

void gao(int p, int val, int op) {
    if(val > n) return;
    if(op == 1) {
        ++vis[p][val];
        if(vis[p][val] == 1) {
            add(p, val, 1);
        }
    } else {
        --vis[p][val];
        if(vis[p][val] == 0) {
            add(p, val, -1);
        }
    }
}

int sz;

void change(int x, int val) {
    if(x <= uu) v[x].val = val;
    else {
        int y, oval = v[x].val;
        v[x].val = val;
        sz = G[x].size();
        for(register int i = 0; i < sz; ++i) {
            y = G[x][i];
            if(y <= uu) {
                gao(y, oval, -1);
                gao(y, val, 1);
            }
        }
    }
}

int mex(int x) {
    int y;
    if(x > uu) {
        memset(tmp, 0, sizeof(tmp));
        vector<int>& list = G[x];
        sz = list.size();
        for(register int i = 0; i < sz; ++i) {
            y = list[i];
            if(v[y].val > (sq + 1)) continue;
            tmp[v[y].val] = true;
        }
        /*
        for(auto y : G[x]) {
            if(v[y].val > (sq + 1)) continue;
            tmp[v[y].val] = true;
        }*/
        for(int i = 1; i <= sq; ++i) {
            if(!tmp[i]) return i;
        }
        return sq + 1;
    } else {
        for(auto y : hb[x]) {
            gao(x, v[y].val, 1);
        }
        int le = 1, ri = n;
        int mid = (le + ri) >> 1;
        while(le < ri) {
            if(query(x, mid) >= mid) {
                le = mid + 1;
            } else {
                ri = mid;
            }
            mid = (le + ri) >> 1;
        }
        for(auto y : hb[x]) {
            gao(x, v[y].val, -1);
        }
        return mid;
    }
}

void init() {
    for(int i = 0; i < sq; ++i) {
        hb[i].clear();
    }
    for(int i = 1; i <= n; ++i) {
        G[i].clear();
    }
}

bool cmp(int a, int b) {
    return v[a].deg > v[b].deg || v[a].deg == v[b].deg && a > b;
}

int main() {
    freopen("F.in", "r", stdin);
    freopen("F.out", "w", stdout);

    clock_t st, ed;
    st = clock();
    int T;
    cin >> T;
    int m, q, val, op;
    while(T--) {
        memset(vis, 0, sizeof(vis));
        memset(C, 0, sizeof(C));
        memset(v, 0, sizeof(v));
        scanf("%d%d", &n, &m);

        init();
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &v[i].val);
            ++v[i].val;
            v[i].id = i;
        }
        for(int i = 1, x, y; i <= m; ++i) {
            scanf("%d%d", &x, &y);
            inp[i] = make_pair(x, y);
            G[x].push_back(y);
            G[y].push_back(x);
        }
        for(int i = 1; i <= n; ++i) {
            sort(G[i].begin(), G[i].end());
            G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
            v[i].deg = G[i].size();
        }
        for(int i = 1; i <= n; ++i) {
            G[i].clear();
        }

        sort(v + 1, v + n + 1);
        for(int i = 1; i <= n; ++i) {
            rk[v[i].id] = i;
        }

        for(int i = 1, x, y; i <= m; ++i) {
            x = rk[inp[i].first], y = rk[inp[i].second];
            G[x].push_back(y);
            G[y].push_back(x);
        }

        for(int x = 1; x <= n; ++x) {
            sort(G[x].begin(), G[x].end());
            auto iter = unique(G[x].begin(), G[x].end());
            //printf("11111\n");
            G[x].erase(iter, G[x].end());
            //printf("2222222\n");
        }
        /*
        for(x = 1; x <= n; ++x) {
            int la = 0;
            reg(i, x) {
                y = e[i].to;
                if(y == la) {
                    printf("sbsbsbsbsbsbsbsb\n");
                    return 0;
                }
                la = y;
            }
        }*/

        uu = 0;
        for(int i = 1; i <= n; ++i) {
            if(v[i].deg > sq) ++uu;
            else break;
        }
        //printf("uu: %d\n", uu);
        for(int x = 1; x <= uu; ++x) {
            for(auto y : G[x]) {
                if(y <= uu) {
                    hb[x].push_back(y);
                }
            }
        }
        for(int x = 1; x <= uu; ++x) {
            for(auto y : G[x]) {
                if(y > uu) {
                    gao(x, v[y].val, 1);
                }
            }
        }
        scanf("%d", &q);

        int x;
        while(q--) {
            scanf("%d%d", &op, &x);
            if(op == 1) {
                scanf("%d", &val);
                change(rk[x], val + 1);
            } else {
                printf("%d\n", mex(rk[x]) - 1);
            }
        }
    }
    ed = clock();
    //cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
}
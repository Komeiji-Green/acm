#include<bits/stdc++.h>
#include<vector>
#include<ctime>
using namespace std;

const int N = 100050, M = 200050;
struct Edge {
    int to, pre;
} e[M];
int last[N], tot = 0;

void ine(int a, int b) {
    ++tot;
    e[tot].to = b;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b) { ine(a, b); ine(b, a); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)
#define rep(i, a, b) for(int i = (a); i <= (b); ++i)

const int maxn = 100050;
const int sq = 455;
// 对于重点，我们维护长度为1e5的cnt数组，另外维护一个树状数组记录本质不同的出现次数
// 对于轻点，主要在查询上把它的信息传给它的邻居们

bool tmp[sq + 10];
int vis[sq][maxn], C[sq][maxn], hb[sq][sq], n, uu;
int rk[maxn]; // id --> rk
struct Point {
    int deg, val, id;
    bool operator<(const Point& b) {
        return deg > b.deg;
    }
} v[maxn];
pair<int, int> inp[maxn];

void add(int p, int x, int v) {
    if(x == 0) {
        printf("!!!!!!!!!\n");
        exit(0);
    }
    for(int i = x; i <= n; i += i & (-i)) {
        C[p][i] += v;
    }
}
int query(int p, int x) {
    int ans = 0;
    for(int i = x; i > 0; i -= i & (-i)) {
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

void change(int x, int val) {
    if(x <= uu) v[x].val = val;
    else {
        int y, oval = v[x].val;
        v[x].val = val;
        reg(i, x) {
            y = e[i].to;
            if(y <= uu) {
                if(oval == 0) {
                    printf("y: %d, n: %d\n", y, n);
                }
                gao(y, oval, -1);
                gao(y, val, 1);
            }
        }
    }
}

int mex(int x) {
    int y, cnt;
    if(x > uu) {
        memset(tmp, 0, sizeof(tmp));
        reg(i, x) {
            y = e[i].to;
            if(v[y].val > (sq + 1)) continue;
            tmp[v[y].val] = true;
        }
        for(int i = 1; i <= sq; ++i) {
            if(!tmp[i]) return i;
        }
        return sq + 1;
    } else {
        cnt = hb[x][0];
        for(int i = 1; i <= cnt; ++i) {
            y = hb[x][i];
            if(v[y].val == 0) printf("!!!!!!!!!!!!!\n");
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
        for(int i = 1; i <= cnt; ++i) {
            y = hb[x][i];
            gao(x, v[y].val, -1);
        }
        return mid;
    }
}

int main() {
    freopen("F.in", "r", stdin);
    freopen("F.out", "w", stdout);

    clock_t st, ed;
    st = clock();
    int T;
    cin >> T;
    int m, x, y, q, val, op;
    while(T--) {
        memset(vis, 0, sizeof(vis));
        memset(C, 0, sizeof(C));
        memset(v, 0, sizeof(v));
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &v[i].val);
            ++v[i].val;
            v[i].id = i;
        }
        for(int i = 1; i <= m; ++i) {
            scanf("%d%d", &x, &y);
            inp[i] = make_pair(x, y);
            ++v[x].deg; ++v[y].deg;
        }
        sort(v + 1, v + n + 1);
        for(int i = 1; i <= n; ++i) {
            rk[v[i].id] = i;
        }
        tot = 0;
        memset(last, 0, sizeof(last));
        for(int i = 1; i <= m; ++i) {
            x = rk[inp[i].first], y = rk[inp[i].second];
            ine2(x, y);
        }

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
        }
        uu = 0;
        for(int i = 1; i <= n; ++i) {
            if(v[i].deg > sq) ++uu;
            else break;
        }
        for(x = 1; x <= uu; ++x) {
            int cnt = 0;
            reg(i, x) {
                y = e[i].to;
                if(y <= uu) {
                    hb[x][++cnt] = y;
                }
            }
            hb[x][0] = cnt;
            if(cnt > uu) {
                printf("????????????????\n");
            }
        }
        for(x = 1; x <= uu; ++x) {
            reg(i, x) {
                y = e[i].to;
                if(y > uu) {
                    gao(x, v[y].val, 1);
                }
            }
        }
        scanf("%d", &q);
        while(q--) {
            scanf("%d%d", &op, &x);
            if(op == 1) {
                scanf("%d", &val);
                //if(rk[x] == 0) return 0;
                if((val + 1) == 0) {
                    printf("val: %d\n", val);
                    return 0;
                }
                change(rk[x], val + 1);
            } else {
                printf("%d\n", mex(rk[x]) - 1);
            }
        }
    }
    ed = clock();
    cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
}
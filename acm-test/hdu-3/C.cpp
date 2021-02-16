#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333, M = 233333;

vector<int> ch[N];
int fn[N], gn[N], clc;
void dfs(int x, int dad) {
    fn[x] = ++clc;
    for(auto y : ch[x]) if(y != dad) dfs(y, x);
    gn[x] = clc;
}

int n;

struct BIT {
    ll C[N];
    void add(int x, ll v) {
        for(int i = x; i <= n; i += i & (-i)) C[i] += v;
    }
    ll query(int x) {
        ll res = 0;
        for(int i = x; i; i -= i & (-i)) res += C[i];
        return res;
    }
} Ta[2], Tb[2];

struct R {
    int x, op, val, t;
};
vector<R> vec[N];

int op[N], xx[N], yy[N], col[N], val[N], tmpc[N], tmpv[N];
ll ans[25][N], oo[N];

int main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; ++i) scanf("%d", &tmpc[i]);
        for(int i = 1; i <= n; ++i) scanf("%d", &tmpv[i]);

        for(int i = 1; i <= n; ++i) ch[i].clear();
        for(int i = 2, u, v; i <= n; ++i) {
            scanf("%d %d", &u, &v);
            ch[u].push_back(v); ch[v].push_back(u);
        }
        clc = 0;
        dfs(1, 0);

        int q; cin >> q;
        for(int i = 1; i <= q; ++i) {
            scanf("%d %d %d", &op[i], &xx[i], &yy[i]);
        }

        for(int b = 0; b < 20; ++b) {
            for(int i = 1; i <= n; ++i) vec[i].clear(), col[i] = tmpc[i], val[i] = tmpv[i];
            for(int i = 1, j, c; i <= n; ++i) {
                c = col[i]; j = ((val[i] >> b) & 1);
                vec[c].push_back(R{i, 1, j, 0});
            }
            for(int i = 1, c, j, x; i <= q; ++i) {
                if(op[i] == 1) {
                    x = xx[i]; j = ((yy[i] >> b) & 1); c = col[x];
                    vec[c].push_back(R{x, -1, (val[x]>>b)&1, i});
                    vec[c].push_back(R{x, 1, j, i});
                    val[x] = yy[i];
                } else {
                    x = xx[i]; c = col[x]; j = yy[i];
                    vec[c].push_back(R{x, -1, (val[x]>>b)&1, i});
                    vec[j].push_back(R{x, 1, (val[x]>>b)&1, i});
                    col[x] = yy[i];
                }
            }

            for(int t = 0; t <= q; ++t) ans[b][t] = 0;
            for(int c = 1, x, val, t, op, l, r; c <= n; ++c) {
                ll cur = 0, cnt[2] = {};
                for(auto pr : vec[c]) {
                    x = pr.x; op = pr.op; val = pr.val; t = pr.t;
                    if(op == 1) {
                        cur = Ta[val^1].query(gn[x]) - Ta[val^1].query(fn[x]-1);
                        cur += Tb[val^1].query(fn[x]);
                        ans[b][t] += cnt[val^1]-cur;
                        Ta[val].add(fn[x], 1); 
                        Tb[val].add(fn[x], 1); Tb[val].add(gn[x] + 1, -1);
                        cnt[val]++;
                    } else {
                        cur = Ta[val^1].query(gn[x]) - Ta[val^1].query(fn[x]-1);
                        cur += Tb[val^1].query(fn[x]);
                        ans[b][t] -= cnt[val^1]-cur;
                        Ta[val].add(fn[x], -1);
                        Tb[val].add(fn[x], -1); Tb[val].add(gn[x] + 1, 1);
                        cnt[val]--;
                    }
                }
                for(auto pr : vec[c]) {
                    x = pr.x; op = pr.op; val = pr.val; t = pr.t;
                    if(op == 1) {
                        Ta[val].add(fn[x], -1); 
                        Tb[val].add(fn[x], -1); Tb[val].add(gn[x] + 1, 1);
                    } else {
                        Ta[val].add(fn[x], 1); 
                        Tb[val].add(fn[x], 1); Tb[val].add(gn[x] + 1, -1);
                    }
                }
            }
        }
        for(int t = 0; t <= q; ++t) {
            oo[t] = 0;
            for(int b = 0; b < 20; ++b) {
                oo[t] += (1ll << b) * ans[b][t];
            }
            if(t) oo[t] += oo[t-1];
            printf("%lld\n", oo[t]);
        }
    }
}
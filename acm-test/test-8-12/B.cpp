#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 1000000 + 5;
const int N = 233333;

struct Edge
{
    int from, to, pre;
    ll w;
} e[M];
int last[M];
int tot = 0;

void ine(int a, int b, ll w)
{
    tot++;
    e[tot].from = a;
    e[tot].to = b;
    e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w)
{
    ine(a, b, w);
    ine(b, a, w);
}

#define reg(i, x) for (int i = last[x]; i; i = e[i].pre)

int n, m, ans[M], es, s, t, ds, dt;

int f[N], w[N];
int find(int x) { return f[x] == x ? x : (f[x] = find(f[x])); }
void merge(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    f[fx] = fy;
    w[fy] += w[fx];
}


void Kruskal() {
    es = 0;
    rep(i, 1, n) { f[i] = i; w[i] = i; }
    rep(i, 1, tot) {
        int x = e[i].from;
        int y = e[i].to;
        if(x == s || x == t || y == s || y == t) continue;
        int fx = find(x), fy = find(y);
        if(fx == fy) continue;
        f[fx] = fy;
        ans[++es] = i;
    }
}

struct Cnc {
    int e[2];  // 0连s，1连t
    int f;  // 代表元素
    int tp;    // 类别
} cnc[N];
int cncnum = 0;
int id[N];  // 代表元素对应连通区域编号
vector<int> bi; // 储存同时连接s、t的区域

int main()
{
    cin >> n >> m;
    int u, v;
    rep(i, 1, m) {
        scanf("%d %d", &u, &v);
        ine2(u, v, 0);
    }
    cin >> s >> t >> ds >> dt;

    Kruskal();

    bool flag = false;
    int p[2] = { s, t };
    rep (k, 0, 1) reg(i, p[k]) {
        if(e[i].to == p[k ^ 1]) { flag = true; continue; }
        int f = find(e[i].to);
        if(!id[f]) {
            cncnum++;
            id[f] = cncnum;
            cnc[cncnum].e[k] = i;
            cnc[cncnum].f = f;
        } else {
            cnc[id[f]].e[k] = i;
        }
    }
    
    rep(i, 1, cncnum) {
        int cnt = 0;
        rep(k, 0, 1) if(cnc[i].e[k]) { cnt++; cnc[i].tp = k; }
        if(cnt == 2) cnc[i].tp = 2;
    }

    rep(i, 1, cncnum) {
        int tp = cnc[i].tp;
        if(tp == 0 || tp == 1) {
            ans[++es] = cnc[i].e[tp];
            if(tp == 0) ds--;
            else dt--;
        }
    }

    bool ok = true;
    rep(i, 1, cncnum) {
        if(cnc[i].tp == 2) {
            bi.push_back(i);
            if(ds < dt) {
                dt--;
                ans[++es] = cnc[i].e[1];
                cnc[i].e[1] = 0;
            } else {
                ds--;
                ans[++es] = cnc[i].e[0];
                cnc[i].e[0] = 0;
            }
        }
    }

    if((ds < 0 || dt < 0) || (ds <= 0 && dt <= 0)) ok = false;
    else if(ds == 0 || dt == 0) {
        int k = (ds == 0);
        bool found = false;
        rep(i, 1, cncnum) {
            if(cnc[i].tp == 2 && cnc[i].e[k]) {
                ans[++es] = cnc[i].e[k];
                found = true;
                break;
            }
        }
        if(!found) ok = false;
    } else {
        bool found = false;
        rep(i, 1, cncnum) {
            if(cnc[i].tp == 2) {
                rep(k, 0, 1) if(cnc[i].e[k]) {
                    ans[++es] = cnc[i].e[k];
                    found = true;
                    break;
                }
                if(found) break;
            }
        }
        if(!found) {
            if(!flag) ok = false;
            else {
                ine(s, t, 0);
                ans[++es] = tot;
            }
        }
    }
    if(es != n - 1) ok = false;
    if(!ok) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        rep(i, 1, es) {
            printf("%d %d\n", e[ans[i]].from, e[ans[i]].to);
        }
    }
}
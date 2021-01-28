#include <cstring>
#include <iostream>
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 1000100;
const int N = 500500;

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

int n, m, clock, pre[N], post[N];


// 获取dfs序
vector<int> vec[N]; // 记录高度为h的点
void dfs(int u, int dad, int dept)
{
    pre[u] = ++clock;
    vec[dept].push_back(u);
    reg(i, u) if(e[i].to != dad)
        dfs(e[i].to, u, dept + 1);
    post[u] = clock;
}


// 树状数组：单点修改，区间查询
int C[N][26];

void add(int id, int val, char c) {
    for(int i = id; i <= clock; i += (i & (-i))) {
        C[i][c - 'a'] += val;
    }
}

int query(int id, char c) {
    int ans = 0;
    for(int i = id; i > 0; i -= (i & (-i))) {
        ans += C[i][c - 'a'];
    }
    return ans;
}

char s[N];
bool ans[N];
struct Query {
    int id, v, h;
} Q[N];

struct cmp {
    bool operator()(const Query& lhs, const Query& rhs) {
        return lhs.h < rhs.h;
    }
};

int main()
{
    cin >> n >> m;
    int p;
    rep(i, 2, n) {
        scanf("%d", &p);
        ine2(i, p, 0);
    }

    dfs(1, 0, 1);

    scanf("%s", s + 1);
    int v, h;
    rep(i, 1, m) {
        scanf("%d %d", &v, &h);
        Q[i].id = i; Q[i].v = v; Q[i].h = h;
    }
    sort(Q + 1, Q + m + 1, cmp());
    
    int curh = 0;
    int cnt, l, r;
    bool ok = true;
    rep(i, 1, m) {
        if(Q[i].h != curh) {
            for(auto x : vec[curh]) {
                add(pre[x], -1, s[x]);
            }
            curh = Q[i].h;
            for(auto x : vec[curh]) {
                add(pre[x], 1, s[x]);
            }
        }
        cnt = 0; 
        l = pre[Q[i].v];
        r = post[Q[i].v];
        ok = true;
        rep(j, 0, 25) {
            if((query(r, 'a' + j) - query(l - 1, 'a' + j)) % 2)
                cnt++;
            if(cnt > 1) {
                ok = false;
                break;
            }
        }
        ans[Q[i].id] = ok;
    }

    rep(i, 1, m) {
        //printf("%d\n", ans[i]);
        printf((ans[i] ? "Yes\n" : "No\n"));
    }
}
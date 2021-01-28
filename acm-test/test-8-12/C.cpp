#include <cstring>
#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 2333334;
const int N = 2333333;

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
void dfs(int u, int dad)
{
    pre[u] = ++clock;
    reg(i, u) if(e[i].to != dad)
        dfs(e[i].to, u);
    post[u] = clock;
}


// 树状数组：单点修改，区间查询
int C[N];

void add(int id, int val) {
    for(int i = id; i <= clock; i += (i & (-i))) {
        C[i] += val;
    }
}

int query(int id) {
    int ans = 0;
    for(int i = id; i > 0; i -= (i & (-i))) {
        ans += C[i];
    }
    return ans;
}

bool state[N];

int main()
{
    cin >> n;
    int u, v;
    rep(i, 1, n - 1) {
        scanf("%d %d", &u, &v);
        ine2(u, v, 0);
    }

    dfs(1, 0);

    rep(i, 1, n) {
        state[i] = true;
        add(pre[i], 1);
    }

    cin >> m;
    char op[4];
    int x;
    rep(i, 1, m) {
        scanf("%s %d", op, &x);
        if(op[0] == 'C') {
            state[x] = !state[x];
            int delta = state[x] ? 1 : -1;
            add(pre[x], delta);
        } else {
            int ans = query(post[x]) - query(pre[x] - 1);
            printf("%d\n", ans);
        }
    }

}
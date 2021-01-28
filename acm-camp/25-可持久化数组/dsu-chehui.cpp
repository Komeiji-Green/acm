#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int maxn = 2005000;

int n, cnt;
int f[maxn], id[maxn], die[maxn], size[maxn], dep[maxn];
int find(int x) { return f[x] == x ? x : find(f[x]); }

struct plot {
    int *p;
    int v;
} pl[5005000]; 
int tot = 0;
void add(int *p) {
    ++tot;
    pl[tot].p = p;
    pl[tot].v = *p;
}
void back(int cur) {
    for(int i = cur + 1; i <= tot; ++i) {
        *(pl[i].p) = pl[i].v;
    }
    tot = cur;
}

void init() {
    for(int i = 0; i <= n; ++i) {
        f[i] = i, id[i] = i, size[i] = 1, dep[i] = 1;
    }
}

void merge(int x, int y) {
    if(die[x] || die[y]) return;
    x = id[x], y = id[y]; 
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    if(dep[fx] > dep[fy]) {
        swap(fx, fy);
    }
    add(&f[fx]);
    f[fx] = fy;
    add(&size[fy]);
    size[fy] += size[fx];
    if(dep[fx] == dep[fy]) {
        add(&dep[fy]);
        dep[fy]++;
    }
}

void erase(int x) {
    if(die[x]) return;
    add(&die[x]);
    die[x] = 1;
    int fx = find(id[x]);
    add(&size[fx]);
    size[fx]--;
}

void move(int x, int y) {
    if(die[x] || die[y]) return;
    int fx = find(id[x]), fy = find(id[y]);
    if(fx == fy) return;
    add(&size[fx]);
    size[fx]--;
    add(&id[x]);
    id[x] = ++cnt;
    merge(x, y);
}

bool check(int x, int y) {
    if(die[x] || die[y]) return false;
    int fx = find(id[x]), fy = find(id[y]);
    return fx == fy;
}

int query(int x) {
    if(die[x]) return 0;
    int fx = find(id[x]);
    return size[fx];
}

struct Q {
    int op, k, x, y, ans;
} q[maxn];

void gao(int i) {
    int op = q[i].op;
    if(op == 0) init();
    else if(op == 1) merge(q[i].x, q[i].y);
    else if(op == 2) erase(q[i].x);
    else if(op == 3) move(q[i].x, q[i].y);
    else if(op == 4) q[i].ans = check(q[i].x, q[i].y);
    else q[i].ans = query(q[i].x);
}

vector<int> nxt[maxn];

void dfs(int i) {
    int cur = tot;
    gao(i);
    for(auto j : nxt[i])
        dfs(j);
    back(cur);
}

int main() {
    int m;
    cin >> n >> m;
    cnt = n; n = n + m;
    q[0].op = 0;
    for(int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &q[i].op, &q[i].k, &q[i].x);
        int op = q[i].op;
        if(op == 1 || op == 3 || op == 4) {
            scanf("%d", &q[i].y);
        }
    }
    for(int i = 1; i <= m; ++i) {
        nxt[q[i].k].push_back(i);
    }
    tot = 0;
    dfs(0);
    for(int i = 1; i <= m; ++i) {
        if(q[i].op == 4) printf(q[i].ans ? "Yes\n" : "No\n");
        else if(q[i].op == 5) printf("%d\n", q[i].ans);
    }
}
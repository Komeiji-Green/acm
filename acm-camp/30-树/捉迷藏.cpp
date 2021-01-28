#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;

const int N=233333, M=233333, lg=40;
struct Edge {
    int from, to, pre;
} e[M];
int last[N], tot;
void ine(int a, int b) {
    ++tot;
    e[tot].from = a; e[tot].to = b; e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b) { ine(a, b); ine(b, a); }
#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

struct heap {
    priority_queue<int> A, B;   // heap = A - B;
    void refresh() {
        while(!B.empty() && B.top() == A.top()) A.pop(), B.pop();
    }
    void insert(int x) { A.push(x); refresh(); }
    void erase(int x) { B.push(x); refresh(); }
    void pop() { A.pop(); refresh(); }
    int top() { return A.top(); }
    int top2() {
        int a = top(); pop();
        int b = top();
        int res = (b == -1 ? -1 : a + b);
        insert(a);
        return res;
    }
};

bool vis[N];
int sz[N], maxx[N], rt, sum;
void getsz(int x, int dad) {
    sz[x] = 1; maxx[x] = 0;
    reg(i, x) {
        int y = e[i].to; if(y == dad || vis[y]) continue;
        getsz(y, x); sz[x] += sz[y]; maxx[x] = max(maxx[x], sz[y]);
    }
    maxx[x] = max(maxx[x], sum - sz[x]);
    if(maxx[x] < maxx[rt]) rt = x;
}

heap nhp[N], ehp[M], ans;
int dep[N], fa[N], eg[N][lg], key[N][lg];

void dfs(int x, int dad, int h, int egid) {
    eg[x][dep[rt]] = egid; key[x][dep[rt]] = h;
    ehp[egid].insert(h);
    reg(i, x) {
        int y = e[i].to; if(y == dad || vis[y]) continue;
        dfs(y, x, h + 1, egid);
    }
}

void build(int x, int dad, int siz, int h) {
    sum = siz; getsz(x, 0); 
    vis[rt] = true; dep[rt] = h; fa[rt] = dad; //printf("rt:%d fa:%d maxx:%d\n", rt, fa[rt], maxx[rt]);

    reg(i, rt) {
        int y = e[i].to; if(vis[y]) continue;
        dfs(y, rt, 1, i);
        nhp[rt].insert(ehp[i].top());
    }
    nhp[rt].insert(0); nhp[rt].insert(0); ans.insert(nhp[rt].top2());

    reg(i, rt) {
        int y = e[i].to; if(vis[y]) continue;
        build(y, rt, sz[y] > sz[rt] ? siz - sz[rt] : sz[y], h + 1);
    }
    rt = dad;
}

//int maxv[N];
void change(int x, int tg) {
    ans.erase(nhp[x].top2());
    if(tg == 1) {
        nhp[x].erase(-1); nhp[x].erase(-1); nhp[x].insert(0); nhp[x].insert(0);
    } else {
        nhp[x].erase(0); nhp[x].erase(0); nhp[x].insert(-1); nhp[x].insert(-1);
    }
    ans.insert(nhp[x].top2());
    //maxv[x] = nhp[x].top2();
    for(int i = fa[x], id, k; i; i = fa[i]) {
        id = eg[x][dep[i]]; k = key[x][dep[i]];
        ans.erase(nhp[i].top2());
        nhp[i].erase(ehp[id].top());
        if(tg == 1) {
            ehp[id].erase(-1); ehp[id].insert(k);
        } else {
            ehp[id].erase(k); ehp[id].insert(-1);
        }
        nhp[i].insert(ehp[id].top());
        ans.insert(nhp[i].top2());
        //maxv[i] = nhp[i].top2();
    }
}

char op[4];
bool st[N];
int main() {
    int n, xx;
    cin >> n;
    for(int i = 2; i <= n; ++i) {
        int uu, vv;
        scanf("%d %d", &uu, &vv);
        ine2(uu, vv);
    }
    rt = 0; maxx[rt] = inf;
    build(1, 0, n, 1); //for(int i = 1; i <= n; ++i) maxv[i] = nhp[i].top2();
    int Q; cin >> Q;
    while(Q--) {
        scanf("%s", op);
        if(op[0] == 'G') {
            printf("%d\n", ans.top());
        } else {
            scanf("%d", &xx);
            if(!st[xx]) change(xx, -1);
            else change(xx, 1);
            st[xx] = !st[xx];
            //for(int i = 1; i <= n; ++i) printf("%d ", maxv[i]); printf("\n");
        }
    }
}
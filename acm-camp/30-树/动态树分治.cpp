#include<bits/stdc++.h>
#include<set>
using namespace std;

const int inf = 0x3f3f3f3f;

struct Node {
    int key; bool tp;
    bool operator<(const Node& rhs) const {
        int a = (tp ? -1 : key);
        int b = (rhs.tp ? -1 : rhs.key);
        return a < b;
    }
};

const int M = 233333, N = 233333, lg = 45;
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

int sum, rt, sz[N], maxx[N];
bool vis[N];
void getsz(int x, int dad) {
    sz[x] = 1; maxx[x] = 0;
    reg(i, x) {
        int y = e[i].to; if(y == dad || vis[y]) continue;
        getsz(y, x); sz[x] += sz[y]; maxx[x] = max(maxx[x], sz[y]);
    }
    maxx[x] = max(maxx[x], sum - sz[x]);
    if(maxx[x] < maxx[rt]) rt = x;
}

int fa[N], dep[N];
int key[N][lg], eg[N][lg];
multiset<int> emp[M], nmp[N];
void dfs(int x, int dad, int h, int id) {
    eg[x][dep[rt]] = id;    // 从属于哪条边
    key[x][dep[rt]] = h; emp[id].insert(h);
    reg(i, x) {
        int y = e[i].to; if(y == dad || vis[y]) continue;
        dfs(y, x, h + 1, id);
    }
}

int getmax(int x) {
    auto it = nmp[x].rbegin();
    int cur = *it; cur += *(++it);
    return cur;
}

int maxv[N];
void dfz(int x, int h) {
    int tmp = rt;
    getsz(x, 0); //printf("tmp:%d x:%d rt:%d h:%d maxrt:%d\n", tmp,x, rt,h,maxx[rt]);
    vis[rt] = true; fa[rt] = tmp; dep[rt] = h;
    reg(i, rt) {
        int y = e[i].to; if(vis[y]) continue;
        dfs(y, rt, 1, i);
        //printf("from:%d to:%d maxv:%d\n",rt,y,*(emp[i].rbegin()));
        nmp[rt].insert(*(emp[i].rbegin()));
        //printf("222\n");
    }
    nmp[rt].insert(0); nmp[rt].insert(0);   // 加两个0表示rt结点
    maxv[rt] = getmax(rt);

    tmp = rt; int psum = sum;
    reg(i, tmp) {
        int y = e[i].to; if(vis[y]) continue;
        rt = tmp;
        sum = (sz[y] > sz[tmp] ? psum - sz[tmp] : sz[y]); dfz(y, h + 1);
    }
}

inline void del(multiset<int>& st, int x) {
    auto it = st.find(x);
    st.erase(it);
}

multiset<int> xf;
bool st[N];
void change(int x, int tg) {
    if(tg == 1) {
        del(nmp[x], -1); del(nmp[x], -1);
        nmp[x].insert(0); nmp[x].insert(0);
    } else {
        del(nmp[x], 0); del(nmp[x], 0);
        nmp[x].insert(-1); nmp[x].insert(-1);
    }
    del(xf, maxv[x]);
    maxv[x] = getmax(x); xf.insert(maxv[x]);
    for(int anc = fa[x], h, ee, kk; anc; anc = fa[anc]) {
        h = dep[anc]; ee = eg[x][h]; kk = key[x][h];
        int la = *(emp[ee].rbegin());
        if(tg == 1) {
            del(emp[ee], -1); emp[ee].insert(kk);
        } else {
            del(emp[ee], kk); emp[ee].insert(-1);
        }
        int ne = *(emp[ee].rbegin());
        del(nmp[anc], la); nmp[anc].insert(ne);
        del(xf, maxv[anc]);
        maxv[anc] = getmax(anc); xf.insert(maxv[anc]);
    }
}

inline int query() {
    return *(xf.rbegin());
}

char op[4];
int main() {
    int n, Q, xx;
    cin >> n;
    for(int i = 2, uv, vv; i <= n; ++i) {
        scanf("%d %d", &uv, &vv);
        ine2(uv, vv);
    }
    rt = 0; maxx[rt] = inf; sum = n; dfz(1, 1);
    for(int i = 1; i <= n; ++i) xf.insert(maxv[i]);
    //for(int i = 1; i <= n; ++i) printf("%d ", fa[i]);
    //printf("\n");
    
    cin >> Q;
    while(Q--) {
        scanf("%s", op);
        if(op[0] == 'G') {
            int dd = query();
            if(dd == -2) dd = -1;
            printf("%d\n", dd);
        } else {
            scanf("%d", &xx);
            if(!st[xx]) change(xx, -1);
            else change(xx, 1);
            st[xx] = !st[xx];
            //for(int i = 1; i <= n; ++i) printf("%d ", maxv[i]);
            //printf("\n");
        }
    }
}
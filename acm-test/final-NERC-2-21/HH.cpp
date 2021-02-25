#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

const int inf = 0x3f3f3f3f;

typedef long long ll;

const int M = 2333333;
const int N = 233333;

vector<int> G[N];

int clc, low[N], dfn[N];
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
int minv[N];    // scc 中的最小下标
void init(int n) {
    clc = 0; sccnum = 0; top = 0;
    for(int i = 1; i <= n; ++i) dfn[i] = 0, low[i] = 0, vis[i] = 0, scc[i] = 0;
}
queue<int> Q;
void tarjan(int cur, int dad) {
    sta[++top] = cur;
    vis[cur] = 0;
    dfn[cur] = ++clc;
    low[cur] = clc;
    Q.push(cur);
    for(int nex : G[cur]) {
        if (!dfn[nex]) { // 树边
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        } else if (!vis[nex]) { // 横边
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if((dfn[cur] == low[cur]) /*|| (dad == 0 && !flag)*/) { 
        sccnum++;
        minv[sccnum] = inf;
        do {
            vis[sta[top]] = 1;
            scc[sta[top]] = sccnum;
            minv[sccnum] = min(minv[sccnum], sta[top]);
        } while(top && sta[top--] != cur);
    }
}

char s[N];
vector<int> vec[N];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, m, nn;
        scanf("%d %d", &n, &m);
        nn = 2 * n + 1;
        while(!Q.empty()) Q.pop(); init(nn);
        for(int i = 2; i <= nn; ++i) G[i].clear();
        //for(int i = 1; i <= nn; ++i) f[i] = i, vec[i].clear(), G[i].clear();
        scanf("%s", s + 1);
        for(int i = 1, u, v, x, y; i <= m; ++i) {
            scanf("%d %d", &u, &v);
            x = u > 0 ? (abs(u)<<1|1) : (abs(u)<<1);
            y = v > 0 ? (abs(v)<<1|1) : (abs(v)<<1);
            G[x^1].push_back(y);
            G[y^1].push_back(x);
        }
        bool f = 1;
        for(int i = 2; i <= nn; ++i) if(!dfn[i]) tarjan(i, 0);
        // 清空Q
        for(int i = 1; i <= n; ++i) if(scc[i<<1] == scc[i<<1|1]) { f = 0; /*printf("11\n");*/ }

        for(int i = 2; i <= nn; ++i) {
            char ch = s[i>>1];
            if(ch == 'A' && minv[scc[i]] != i) { f = 0; /*printf("11\n");*/ }
        }

        while(!Q.empty()) Q.pop(); init(nn);
        for(int i = 1; i <= n && f; ++i) {
            if(s[i] == 'A') {
                G[i<<1].push_back(i<<1|1);
                tarjan(i<<1, 0); if(!dfn[i<<1|1]) tarjan(i<<1|1, 0);
                while(!Q.empty()) {
                    int x = Q.front(); Q.pop();
                    if((x>>1) != i && s[x>>1] == 'A') { f = 0; /*printf("11\n");*/ }
                    if(scc[x] == scc[x^1]) { f = 0; /*printf("11\n");*/ }
                }
                G[i<<1].pop_back();
            }
        }
        while(!Q.empty()) Q.pop(); init(nn);
        for(int i = 1; i <= n && f; ++i) {
            if(s[i] == 'A') {
                G[i<<1|1].push_back(i<<1);
                tarjan(i<<1, 0); if(!dfn[i<<1|1]) tarjan(i<<1|1, 0);
                while(!Q.empty()) {
                    int x = Q.front(); Q.pop();
                    if(scc[x] == scc[x^1]) { f = 0; /*printf("11\n");*/ }
                }
                G[i<<1|1].pop_back();
            }
        }
        if(f) {
            printf("TRUE\n");
        } else {
            printf("FALSE\n");
        }
    }
}
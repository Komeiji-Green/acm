#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
const int N = 233333;

struct Edge {
    int to, pre;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b) {
    ++tot;
    e[tot].to = b;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b) { ine(a, b); ine(b, a); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


int clc, low[N], dfn[N];
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
void init(int n) {
    tot = 0; clc = 0; sccnum = 0; top = 0;
    for(int i = 1; i <= n; ++i) last[i] = 0, vis[i] = 0, low[i] = 0, dfn[i] = 0;
}
void tarjan(int cur, int dad) {
    sta[++top] = cur;
    vis[cur] = 0;
    dfn[cur] = ++clc;
    low[cur] = clc;
    reg(i, cur) {
        int nex = e[i].to;
        if (!dfn[nex]) { // 树边
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        } else if (!vis[nex]) { 
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if(dfn[cur] == low[cur]) { 
        sccnum++;
        do {
            vis[sta[top]] = 1;
            scc[sta[top]] = sccnum;
        } while(top && sta[top--] != cur);
    }
}

char s[N];
int tag[N], pos[N];
int id[3][3] = {
    {-1, 0, 1},
    {0, -1, 1},
    {0, 1, -1}
};
struct op {
    int u, v, i, j;
} uu[N];
int main() {
	int n, m, d;
    cin >> n >> d;
    scanf("%s", s + 1);
    int num = 0;
    for(int i = 1; i <= n; ++i) {
        if(s[i] == 'x') {
            pos[num++] = i;
        } else {
            tag[i] = s[i] - 'a';
        }
    }
    cin >> m;
    int u, v, a, b;
    char aa[4], bb[4];
    for(int i = 1; i <= m; ++i) {
        scanf("%d %s %d %s", &u, aa, &v, bb);
        uu[i].u = u, uu[i].v = v; uu[i].i = aa[0]-'A'; uu[i].j = bb[0]-'A';
    } 
    int sz = (1<<d);
    bool f = 0;
    for(int i = 0; i < sz && !f; ++i) {
        for(int j = 0; j < d; ++j) {
            if((1<<i)&j) tag[pos[j]] = 1;
            else tag[pos[j]] = 0;
        }
        int nn = (n<<1|1);
        init(nn);
        for(int j = 1, x, y, k; j <= m; ++j) {
            u = uu[j].u, v = uu[j].v, a = uu[j].i, b = uu[j].j;
            if((k = id[tag[u]][a])==-1) x = 0;
            else x = ((u<<1)|k);
            if((k = id[tag[v]][b])==-1) y = 0;
            else y = ((v<<1)|k);
            if(x == 0) continue;
            if(y == 0) ine(x, x^1);
            else {
                ine(x, y); ine(y^1, x^1);
            }
        }
        for(int j = 2; j <= nn; ++j) if(!dfn[j]) tarjan(j, 0);
        f = 1;
        for(int j = 1; j <= n; ++j) {
            if(scc[j<<1] == scc[j<<1|1]) {
                f = 0; break;
            }
        }
        if(f) {
            for(int j = 1; j <= n; ++j) {
                int cs = (scc[j<<1] > scc[j<<1|1]); // choose cs
                if(tag[j] == 0) {
                    putchar(cs ? 'C' : 'B');
                } else if(tag[j] == 1) {
                    putchar(cs ? 'C' : 'A');
                } else if(tag[j] == 2) {
                    putchar(cs ? 'B' : 'A');
                }
            }
            printf("\n");
        }
    }
    if(!f) printf("-1\n");
    return 0;
}

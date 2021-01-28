#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
const int N = 2333333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


int clock, low[N], dfn[N], iscut[N];
// 强连通分量
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
//int nums[N], minv[N], cost[N]; // 结点数、最小权
void tarjan(int cur, int dad)
{
    sta[++top] = cur;
    vis[cur] = 0;
    dfn[cur] = ++clock;
    low[cur] = clock;
    //bool flag = false;
    reg(i, cur)
    {
        //flag = true;
        int nex = e[i].to;
        if (!dfn[nex]) { // 树边
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        }
        else if (!vis[nex]) { // 防重边
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if((dfn[cur] == low[cur]) /*|| (dad == 0 && !flag)*/) { 
        sccnum++;
        do {
            vis[sta[top]] = 1;
            scc[sta[top]] = sccnum;
        } while(top && sta[top--] != cur);
    }
}

int main() {
	int n, m;
	cin >> n >> m;
	int u, v, a, b;
	rep(i, 1, m) {
		scanf("%d %d %d %d", &u, &v, &a, &b);
		ine(u<<1|(a ^ 1), v<<1|b, 0);
		ine(v<<1|(b ^ 1), u<<1|a, 0);
	}
	rep(i, 1, 2 * n) {
		if(!dfn[i]) tarjan(i, 0);
	}
	rep(i, 1, n) {
		if(scc[i<<1] == scc[i<<1|1]) 
	}
}




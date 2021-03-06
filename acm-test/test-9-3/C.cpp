#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 5333333;
const int N = 2333;

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

struct Link {
	int l, r;
} link[N];

int main() {
	int n, m;
	cin >> n >> m;
	
	int u, v, c;
	char op[10];
	rep(i, 1, m) {
		scanf("%d %d %d %s", &u, &v, &c, op);
		u++; v++;
		if(op[0] == 'A') {
			if(c == 1) {
				ine(u<<1, u<<1|1, 0);
				ine(v<<1, v<<1|1, 0);
			} else {
				ine(u<<1|1, v<<1, 0);
				ine(v<<1|1, u<<1, 0);
			}
		} else if(op[0] == 'O') {
			if(c == 0) {
				ine(u<<1|1, u<<1, 0);
				ine(v<<1|1, v<<1, 0);
			} else {
				ine(u<<1, v<<1|1, 0);
				ine(v<<1, u<<1|1, 0);
			}
		} else if(op[0] == 'X') {
			if(c == 0) {
				ine(u<<1, v<<1, 0);
				ine(u<<1|1, v<<1|1, 0);
				ine(v<<1, u<<1, 0);
				ine(v<<1|1, u<<1|1, 0);
			} else {
				ine(u<<1, v<<1|1, 0);
				ine(u<<1|1, v<<1, 0);
				ine(v<<1, u<<1|1, 0);
				ine(v<<1|1, u<<1, 0);
			}
		}
	}
	
	rep(i, 1, 2 * n) {
		if(!dfn[i]) tarjan(i, 0);
	}
	rep(i, 1, n) {
		if(scc[i<<1] == scc[i<<1|1]) {
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	return 0;
}

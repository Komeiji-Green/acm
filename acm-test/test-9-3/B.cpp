#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
const int N = 233333;

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


int clc, low[N], dfn[N];
// 强连通分量
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
//int nums[N], minv[N], cost[N]; // 结点数、最小权
void tarjan(int cur, int dad)
{
    sta[++top] = cur;
    vis[cur] = 0;
    dfn[cur] = ++clc;
    low[cur] = clc;
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

int age[N], tag[N];	// 0 -- old -- A , 1 -- young -- B (严格） 

int main() {
	int n, m;
	while(scanf("%d %d", &n, &m) != EOF && n && m) {
		
		tot = 0;
		memset(last, 0, sizeof(last));
		clc = 0;
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(vis, 0, sizeof(vis));
		top = 0; sccnum = 0;
		
		int sum = 0;
		rep(i, 1, n) {
			scanf("%d", &age[i]);
			sum += age[i];
		}
		rep(i, 1, n) {
			if(age[i] * n < sum)
				tag[i] = 1;
			else tag[i] = 0;
		}
	
		int u, v;
		rep(i, 1, m) {
			scanf("%d %d", &u, &v);
			if(tag[u] == tag[v]) {
				ine(u<<1, v<<1|1, 0);
				ine(u<<1|1, v<<1, 0);
				ine(v<<1, u<<1|1, 0);
				ine(v<<1|1, u<<1, 0);
			} else {
				ine(u<<1, v<<1|1, 0);
				ine(v<<1, u<<1|1, 0);
			}
		}
		
		rep(i, 1, 2 * n) {
			if(!dfn[i]) tarjan(i, 0);
		}
		bool flag = true;
		rep(i, 1, n) {
			if(scc[i<<1] == scc[i<<1|1]) {
				printf("No solution.\n");
				flag = false;
				break;
			}
		}
		if(!flag) continue;
		rep(i, 1, n) {
			if(scc[i<<1] < scc[i<<1|1]) {
				printf("C\n");
			} else {
				printf(tag[i] ? "B\n" : "A\n");
			}
		}
	}
}

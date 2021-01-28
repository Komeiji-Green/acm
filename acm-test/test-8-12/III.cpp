#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 105000;
const int N = 55000;

struct Edge
{
    int from, to, pre;
    ll w;
} e[M];
int last[N];
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

int clc, low[N], dfn[N], iscut[N], vis[N];
int sta[233333], top = 0;
vector<int> bcc[N]; int bccnum = 0;

void tarjan(int x, int dad) {
	sta[++top] = x;
	low[x] = dfn[x] = ++clc;
	vis[x] = 0;
	int child = 0;
	reg(i, x) {
		int y = e[i].to;
		if(!dfn[y]) {	// 树边 
			child++;
			tarjan(y, x);
			low[x] = min(low[x], low[y]);
			if(!vis[y] && low[y] == dfn[x]) {
				iscut[x] = 1;
				bccnum++;
				vector<int> temp;
				swap(bcc[bccnum], temp);
				do {
					bcc[bccnum].push_back(sta[top]);
					vis[sta[top]] = 1;
				} while (sta[top--] != y);
				bcc[bccnum].push_back(x);
			}
		} else if (!vis[y]) {  // 未取出的回边
			low[x] = min(low[x], dfn[y]); 
		}
	}
	if(dad == 0 && child == 1)
		iscut[x] = 0;
}

int main() {
	int cas = 0;
	int n, m;
	while(scanf("%d", &m) != EOF && m) {
		cas++;
		n = m + 1;
		
		tot = 0;
        memset(last, 0, sizeof(last));
        clc = 0;
        memset(low, 0, sizeof(low));
        memset(dfn, 0, sizeof(dfn));
        memset(iscut, 0, sizeof(iscut));
        memset(vis, 0, sizeof(vis));
        top = bccnum = 0;
        
        int u, v;
		rep(i, 1, m) {
			scanf("%d %d", &u, &v);
			ine2(u, v, 0);
		}
		
		tarjan(1, 0);
		
		ll ans = 0, sum = 1;
		rep(i, 1, bccnum) {
			int cnt = 0;	// 割点总数 
			for(auto x : bcc[i]) {
				if(iscut[x]) {
					cnt++;
				}
			}
			if(cnt == 1) {
				ans++;
				sum *= bcc[i].size() - 1;
			}
		}
		if(bccnum == 1) {
			ans = 2;
			sum = bcc[1].size() * (bcc[1].size() - 1) / 2;
		}
		
		printf("Case %d: %lld %lld\n", cas, ans, sum);
	}
}





#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 333333, M = 2 * N;
struct Edge {
	int to, pre;
} e[M];
int last[N], tot;
void ine(int a, int b) {
	++tot;
	e[tot].to = b; e[tot].pre = last[a];
	last[a] = tot;
}
inline void ine2(int a, int b) {
	ine(a, b); ine(b, a);
}
#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int col[N], vis[N];
void dfs(int x) {
	if(vis[x]) return;
	vis[x] = 1;
	if(col[x] == 1) {
		reg(i, x) col[e[i].to] = -1;
		reg(i, x) dfs(e[i].to);
	} else {
		reg(i, x) {
			int y = e[i].to;
			if(col[y] == -1) continue;
			col[y] = 1;
			dfs(y);
		}
	}
}
int ans[N];
int main() {
	int T;
	cin >> T;
	int n, m;
	while(T--) {
		scanf("%d %d", &n, &m);
		tot = 0;
		for(int i = 1; i <= n; ++i) last[i] = 0, vis[i] = 0, col[i] = 0;
		for(int i = 1, u, v; i <= m; ++i) {
			scanf("%d %d", &u, &v);
			ine2(u, v);
		}
		col[1] = 1;
		dfs(1);
		bool f = 1;
		int cnt=  0;
		for(int i = 1; i <= n; ++i) {
			if(!vis[i]) f = 0;
			if(col[i] == 1) ans[++cnt] = i;
		}
		if(f) {
			printf("YES\n");
			printf("%d\n", cnt);
			for(int i =1; i <= cnt; ++i) printf("%d ", ans[i]);
			printf("\n");
		} else {
			printf("NO\n");
		}
	}
} 

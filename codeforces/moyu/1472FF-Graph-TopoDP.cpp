#include<bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;

const int N = 233333, M = 466666;
struct Edge {
	int from, to, pre;
};
struct Node {
	int id, d;
	bool operator<(const Node& b) {
		return d < b.d;
	}
} uu[N];
int ans[N], dp[N];
struct Graph {
	Graph() {}
	Edge e[M];
	int last[N], tot;
	int deg[N], a[N];
	bool vis[N];
	void clr(int n) {
		tot = 0;
		for(int i = 1; i <= n; ++i) last[i] = 0, vis[i] = 0;
	}
	void ine(int a, int b) {
		++tot;
		e[tot].from = a; e[tot].to = b; e[tot].pre = last[a];
		last[a] = tot;
	}
	void getd(int n) {
		for(int i = 1; i <= n; ++i) uu[i].d = inf;
		uu[1].d = 0;
		queue<int> q;
		q.push(1); 
		while(!q.empty()) {
			int x = q.front(); q.pop();
			if(vis[x]) continue;
			vis[x] = 1;
			for(int i = last[x], y; i; i = e[i].pre) {
				y = e[i].to;
				if(!vis[y]) {
					uu[y].d = min(uu[y].d, uu[x].d + 1);
					q.push(y);
				}
			}
		}
	}
	void topo(int n) {
		queue<int> q;
		for(int i = 1; i <= n; ++i) deg[i] = 0;
		for(int i = 1; i <= tot; ++i) deg[e[i].to]++;
		for(int i = 1; i <= n; ++i) if(!deg[i]) q.push(i);
		int cnt = 0;
		while(!q.empty()) {
			int x = q.front(); q.pop();
			a[++cnt] = x;
			for(int i = last[x]; i; i = e[i].pre) {
				int y = e[i].to;
				if(!(--deg[y])) q.push(y);
			}
		}
		//for(int i = 1; i <= n; ++i) printf("%d ", a[i]); printf("\n");
		for(int i= 1; i <= n; ++i) {
			int x = a[i];
			for(int j = last[x]; j; j = e[j].pre) {
				int y = e[j].to;
				dp[y] = min(dp[y], dp[x]);
			}
			//printf("%d: ", i);for(int ii = 1; ii <= n; ++ii) printf("%d ", dp[ii]);printf("\n");
		}
	}
} G, iG;

int main() {
	int T;
	cin >> T;
	int n, m;
	while(T--) {
		scanf("%d %d", &n, &m);
		G.clr(n); iG.clr(n); 
		for(int i = 1; i <= n; ++i) {
			uu[i].id = i;
		}
		int u, v;
		while(m--) {
			scanf("%d %d", &u, &v);
			G.ine(u, v);
		}
		G.getd(n);
		for(int i = 1;  i<= n; ++i) dp[i] = n + 1;
		for(int i = 1; i <= G.tot; ++i) {
			int u = G.e[i].from, v = G.e[i].to;
			if(uu[u].d >= uu[v].d) { //printf("!!!: %d >= %d\n", u, v);
				dp[u] = min(dp[u], uu[v].d);
				//li[v].push_back(u);
			} else {
				iG.ine(v, u);
			}
		}
		//printf("dis: ");for(int ii = 1; ii <= n; ++ii) printf("%d ", uu[ii].d);printf("\n");
		for(int i = 1; i <= n; ++i) ans[i] = uu[i].d;
		//printf("0: ");for(int ii = 1; ii <= n; ++ii) printf("%d ", dp[ii]);printf("\n");
		iG.topo(n);
		for(int i = 1; i <= n; ++i) printf("%d ", min(ans[i], dp[i]));
		printf("\n");
	}
	
/*
1
7 10
1 4
4 2
4 7
1 6
7 5
5 3
3 4
3 1
4 3
4 5
	*/
} 

#include<bits/stdc++.h>
using namespace std;

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
int ans[N];
struct Graph {
	Graph() {}
	Edge e[M];
	int last[N], tot;
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
		for(int i = 1;  i<= n; ++i) uu[i].d = n + 1;
		uu[1].d = 0;
		queue<int> q;
		q.push(1); 
		while(!q.empty()) {
			int x = q.front(); q.pop();
			if(vis[x]) continue;
			vis[x] = 1;
			for(int i = last[x], y; i; i = e[i].pre) {
				y = e[i].to;
				uu[y].d = min(uu[y].d, uu[x].d + 1);
				q.push(y);
			}
		}
	}
	void dfs(int x, int w) {
		if(vis[x]) return;
		vis[x] = 1;
		ans[x] = min(ans[x], w);
		for(int i = last[x], y; i; i = e[i].pre) {
			y = e[i].to;
			dfs(y, w);
		}
	}
} G, iG;

vector<int> li[N];
int main() {
	int T;
	cin >> T;
	int n, m;
	while(T--) {
		scanf("%d %d", &n, &m);
		G.clr(n); iG.clr(n); 
		for(int i = 1; i <= n; ++i) {
			uu[i].id = i; li[i].clear();
		}
		int u, v;
		while(m--) {
			scanf("%d %d", &u, &v);
			G.ine(u, v);
		}
		G.getd(n);
		for(int i = 1; i <= G.tot; ++i) {
			int u = G.e[i].from, v = G.e[i].to;
			if(uu[u].d >= uu[v].d) {
				li[v].push_back(u);
			} else {
				iG.ine(v, u);
			}
		}
		for(int i = 1; i <= n; ++i) ans[i] = uu[i].d;
		sort(uu + 1, uu + n + 1);
		for(int i = 1; i <= n; ++i) {
			int x = uu[i].id, dis = uu[i].d;
			for(auto y : li[x]) {
				iG.dfs(y, dis);
			}
		}
		for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
		printf("\n");
	}
} 

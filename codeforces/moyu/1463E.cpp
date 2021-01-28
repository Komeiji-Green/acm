#include<bits/stdc++.h>
using namespace std;

const int N = 330000;
int fa[N], pre[N], nex[N], id[N], deg[N], head[N], a[N], tot;
bool vis[N];
vector<int> ch[N];
int main() {
	int n, k; cin >> n>> k;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &fa[i]);
		ch[fa[i]].push_back(i);
	}
	for(int i = 1, x, y; i <= k; ++i) {
		scanf("%d %d", &x, &y);
		nex[x] = y; pre[y] = x;
	}
	for(int x = 1; x <= n; ++x) {
		if(pre[x] || id[x]) continue;
		++tot;
		head[tot] = x;
		for(int y = x; y; y = nex[y]) {
			id[y] = tot;
			if(fa[y] && id[fa[y]] != tot) deg[tot]++;
		}
	}
	int cnt = 0;
	queue<int> q;
	for(int i = 1; i <= tot; ++i) {
		if(!deg[i]) q.push(i);
	}
	while(!q.empty()) {
		int cur = q.front(); q.pop();
		a[++cnt] = cur;
		for(int x = head[cur]; x; x = nex[x]) {
			for(auto y : ch[x]) {
				if(id[y] == cur) continue;
				if(!(--deg[id[y]])) {
					q.push(id[y]);
				}
			}
		}
	}
	if(cnt != tot) {
		printf("0\n");
	} else {
		for(int i = 1, cur; i <= cnt; ++i) {
			cur = a[i];
			for(int x = head[cur]; x; x = nex[x]) {
				printf("%d ", x);
			}
		}
		printf("\n");
	}
} 

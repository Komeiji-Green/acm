#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

int d[20], len[20];
struct state  {
	int x[11], y[11];
	bool vis[8][8];
};

struct _hash {
	size_t operator() (const state& st) const {
		size_t res = d[1] == 1 ? st.y[1] : st.x[1];
		for(int i = 2; i <= n; ++i) {
			res = res * 19260817 + (d[i] == 1 ? st.y[i] : st.x[i]);
		}
		return res;
	}
};

struct cmp {
	bool operator() (const state& a, const state& b) const {
		for(int i = 1; i <= n; ++i) {
			if(a.x[i] != b.x[i] || a.y[i] != b.y[i]) return false; 
		}
		return true;
	}
};

unordered_set<state, _hash, cmp> vis;

state t;
int bfs(state s) {
	if(s.x[1]!=3||d[1]==2) return -1;
	queue<pair<state, int> > q;
	q.push(make_pair(s, 0));
	state cur, nex; int dis;
	while(!q.empty()) {
		cur = q.front().first; dis = q.front().second; q.pop();
		if(vis.count(cur)) continue;
		vis.insert(cur);
		if(dis > 10) return -1;
		if(dis + 7 - cur.y[1] > 10) continue;
		if(cur.y[1] + len[1] == 7) return dis + len[1];
		for(int i = 1, xx, yy; i <= n; ++i) {
			xx = cur.x[i], yy = cur.y[i]; 
			if(d[i] == 1) {
				if(i == 1 && yy<=1 && yy+len[i]>=2) {
					nex = cur;
					nex.vis[xx][yy-1+len[i]]=0;
					nex.y[i]--;
					q.push(make_pair(nex, dis + 1));
				} else if(!cur.vis[xx][yy-1]) {
					nex = cur;
					nex.vis[xx][yy-1]=1;
					nex.vis[xx][yy-1+len[i]]=0;
					nex.y[i]--;
					q.push(make_pair(nex, dis + 1));
				}
				if(i == 1 && yy<=0 && yy+len[i]>=1 && !cur.vis[xx][yy+len[i]]) {
					nex = cur;
					nex.vis[xx][yy+len[i]]=1;
					nex.y[i]++;
					q.push(make_pair(nex, dis + 1));
				} else if(!cur.vis[xx][yy+len[i]]) {
					nex = cur;
					nex.vis[xx][yy+len[i]]=1;
					nex.vis[xx][yy]=0;
					nex.y[i]++;
					q.push(make_pair(nex, dis + 1));
				}
			} else {
				if(!cur.vis[xx-1][yy]) {
					nex = cur;
					nex.vis[xx-1][yy]=1;
					nex.vis[xx-1+len[i]][yy]=0;
					nex.x[i]--;
					q.push(make_pair(nex, dis + 1));
				}
				if(!cur.vis[xx+len[i]][yy]) {
					nex = cur;
					nex.vis[xx+len[i]][yy]=1;
					nex.vis[xx][yy]=0;
					nex.x[i]++;
					q.push(make_pair(nex, dis + 1));
				}
			}
		}		
	}
	return -1;
}

state o;
int a[10][10];
int main() {
	for(int i = 1; i <= 6; ++i) {
		for(int j = 1; j <= 6; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	for(int i = 0; i <= 7; ++i) o.vis[i][0] = 1, o.vis[i][7] = 1;
	for(int j = 0; j <= 7; ++j) o.vis[0][j] = 1, o.vis[7][j] = 1;
	
	for(int i = 1; i <= 6; ++i) {
		for(int j = 1; j <= 6; ++j) {
			if(!a[i][j]) continue;
			o.vis[i][j]=1;
			if(d[a[i][j]]) continue;
			len[a[i][j]] = 1; o.x[a[i][j]] = i; o.y[a[i][j]] = j; 
			for(int k = j + 1; k <= j + 2; ++k) {
				if(a[i][k] == a[i][j]) d[a[i][j]] = 1, len[a[i][j]]++;
			}
			if(d[a[i][j]]) continue;
			for(int k = i + 1; k <= i + 2; ++k) {
				if(a[k][j] == a[i][j]) d[a[i][j]] = 2, len[a[i][j]]++;
			}
		}
	}
	for(int i = 1; d[i]; ++i) ++n;
	/*for(int i = 1; i <= n; ++i) {
		printf("%d: d:%d len:%d x:%d y:%d\n", i, d[i], len[i], o.x[i], o.y[i]);
	}*/
	int ans = bfs(o);
	printf("%d\n", ans);
} 

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
/*struct Point {
	int col;
	ll val;
	bool operator<(const Point& b) {
		return val < b.val || val == b.val && col < b.col;
	}
	bool operator==(const Point& b) {
		return val == b.val;
	}
} v[maxn], u[maxn];*/

vector<int> tmp[maxn], vec[maxn];
int ls[maxn];
struct DD {
	int sz, id;
	bool operator<(const DD& b) {
		return sz > b.sz;
	}
} vs[maxn];

struct Edge {
	int val, id, pre;
} e[42000006];
int last[maxn], vis[maxn], es;
void ine(int a, int val, int id) {
	++es;
	e[es].id = id; e[es].val = val; e[es].pre = last[a];
	last[a] = es;
}

bool chk(vector<int>& a, vector<int>& b) {
	int sa = a.size(), sb = b.size();
	int i = 0, j = 0, cnt = 0;
	while(i < sa && j < sb) {
		if(a[i]==b[j]) {
			++cnt; ++i; ++j;
		} else if(a[i] < b[j]) ++i;
		else ++j;
	}
	return cnt > 1;
}
int main() {
	int T, n, k;
	cin >> T;
	int tot, cnt;
	int sum = 0;
	while(T--) {
		tot = 0;
		cnt = 0;
		sum = 0;
		scanf("%d", &n);
		int tot = 0;
		for(int i = 1, x; i <= n; ++i) {
			scanf("%d", &k);
			tmp[i].clear();
			for(int j = 0; j < k; ++j) {
				scanf("%d", &x); tmp[i].push_back(x);
				ls[++tot] = x;
			}
			vs[i].id=i; vs[i].sz = k;
			sum += k;
		}
		sort(vs + 1, vs + n + 1);
		for(int i = 1; i <= n; ++i) vec[i] = tmp[vs[i].id];
		
		sort(ls + 1, ls + tot + 1);
		tot = unique(ls + 1, ls + tot + 1) - ls - 1;
		for(int i = 1; i <= n; ++i) {
			int sz = vec[i].size();
			for(int j = 0; j < sz; ++j) vec[i][j] = lower_bound(ls + 1, ls + tot + 1, vec[i][j]) - ls;
			sort(vec[i].begin(), vec[i].end());	
		}
		
		int sq, bd;
		for(sq = 1; sq * sq < sum; ++sq);
		sq /= 2;
		for(bd = 1; bd <= n && vs[bd].sz > sq; ++bd);
		bd = min(bd, n);
		bool f = 0;
		/*bool ck = 1;
		for(int i = 1; i < n; ++i) {
			if(vec[i].size() < vec[i+1].size() || vs[i].sz < vs[i + 1].sz) ck = 0;
		} 
		if(!ck) return 0;*/
		for(int i = 1; i <= bd && !f; ++i) {
			for(auto x : vec[i]) vis[x] = i;
			for(int j = i + 1; j <= n && !f; ++j) {
				int cnt = 0;
				for(auto y : vec[j]) if(vis[y]==i) ++cnt;
				if(cnt > 1) {
					f = 1;
					printf("%d %d\n", vs[i].id, vs[j].id);
				}
			}
		}
		for(int x = 1; x <= tot; ++x) vis[x] = 0;
		if(f) continue;
		
		for(int x = 0; x <= tot; ++x) last[x] = 0; es = 0;
		for(int i = bd + 1, sz; i <= n; ++i) {
			sz = vec[i].size();
			vector<int>& li = vec[i];
			for(int j = 0; j < sz; ++j)	for(int dd = j + 1; dd < sz; ++dd) {
				ine(li[j], li[dd], i);
			}
		}
		for(int x = 1; x <= tot && !f; ++x) {
			queue<int> q;
			for(int i = last[x], val, id; i; i = e[i].pre) {
				val = e[i].val; id = e[i].id;
				if(!vis[val]) {
					vis[val] = id; q.push(val);
				} else {
					f = 1;
					printf("%d %d\n", vs[vis[val]].id, vs[id].id);
					break;
				}
			}
			while(!q.empty()) {
				vis[q.front()]=0; q.pop();
			}
		}
		if(!f) printf("-1\n");
	}
}

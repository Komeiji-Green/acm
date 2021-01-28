#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

map<string, int> mp[5050];

char s[5050];
vector<int> ch[5050];
bool vis[5050];
int f[5050];
int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}
void merge(int x, int y) {
	int fx = find(x); int fy = find(y);
	f[fx] = fy;
}
void dfs(int x) {
	for(auto p : ch[x]) {
		if(x && p && !vis[x] && !vis[p]) merge(x, p);
		//printf("vis: %d %d\n", x, p);
		dfs(p);
	}
}
int tot = 0;
int main() {
	int T;
	cin >> T;
	int n, m, q;
	int len; string cur;
	while(T--) {
		scanf("%d %d", &n, &m);
		int sz = n + m;
		for(int i = 1; i <= sz; ++i) {
			scanf("%s", s);
			len = strlen(s);
			q = 0;
			for(int j = 0; j <= len; ++j) {
				if(j == len || s[j] == '/') {
					if(mp[q].count(cur)) {
						q = mp[q][cur];
					} else {
						++tot;
						mp[q][cur] = tot; //cout << "!!" << cur <<  " " << tot << endl;
						ch[q].push_back(tot);
						q = tot;
					}
					if(i > n) vis[q] = 1;
					cur = "";
				} else {
					cur += s[j];
				}
			}
		}
		for(int i = 1; i <= tot; ++i) f[i] = i;
		dfs(0);
		int ans = 0;
		for(int i = 1; i <= tot; ++i) {
			if(!vis[i] && f[i] == i) {
				++ans; //printf("id: %d\n", i);
			}
		}
		printf("%d\n", ans);
		for(int i = 0; i <= tot; ++i) {
			ch[i].clear();
			mp[i].clear();
			vis[i] = 0;
		}
		tot  = 0;
	}
} 

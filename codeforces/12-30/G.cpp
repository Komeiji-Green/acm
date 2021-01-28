#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;
const int N = 100050;
const int M = 1000050;

int invf[N], f[N];

int tr[M][26], tot = 0;
int fail[M];

int insert(char *s) {
	int p = 0;
	for(int i = 0, k; s[i]; ++i) {
		k = s[i] - 'a';
		if(!tr[p][k]) tr[p][k] = ++tot;
		p = tr[p][k];
	}
	return p;
}
void build() {
	queue<int> q;
	memset(fail, 0, sizeof(fail));
	for(int i = 0; i < 26; ++i) {
		if(tr[0][i]) q.push(tr[0][i]);
	}
	while(!q.empty()) {
		int k = q.front(); q.pop();
		for(int i = 0; i < 26; ++i) {
			if(tr[k][i]) {
				fail[tr[k][i]] = tr[fail[k]][i];
				q.push(tr[k][i]);
			} else
				tr[k][i] = tr[fail[k]][i];
		}
	}
}

int n;
int clc, dfn[M], las[M];
int cnt[27][M], num, st;
int sum[27];

string s;
void query(int m, int id) {
	int p = 0, sz = s.size();
	int *c = cnt[id];
	for(int i = 0; i < sz; ++i) {
		p = tr[p][s[i]-'a'];
		if(i < m) --c[dfn[p]];
		else ++c[dfn[p]];
	}
}

char tst[N], name[M];
vector<int> ch[M];

void dfs(int x) {
	dfn[x] = ++clc;
	for(auto y : ch[x]) dfs(y);
	las[x] = clc;
}

struct Q {
	int id, p, o;
	bool operator<(const Q& b) {
		return id < b.id;
	}
} uu[N];
int ans[N];
int q;

inline void pre(int id) {
	int *c = cnt[id];
	for(int i = 1; i <= clc; ++i) c[i] += c[i-1]; 
}
void gao() {
	num = 0;
	int t = 1;
	int sz = s.size();
	query(0, 26); pre(26);
	for(; t <= q && uu[t].id <= 0; ++t) ans[uu[t].o] = cnt[26][las[uu[t].p]]-cnt[26][dfn[uu[t].p]-1];
	for(int i = 1; i <= n; ++i) {
		if(s.size() >= M) break;
		num = i;
		sz = s.size();
		s = s + tst[i-1] + s;
		for(int x = 0; x <= clc; ++x) cnt[26][x] = 0; 
		query(0, 26); pre(26);
		for(; t <= q && uu[t].id <= i; ++t) ans[uu[t].o] = cnt[26][las[uu[t].p]]-cnt[26][dfn[uu[t].p]-1];
	}
	//s[sz] = 'a' to 'z'
	for(int i = 0; i < 26; ++i) {
		s[sz] = 'a' + i;
		query(sz, i); pre(i);
	}
	sum[26] = invf[num];
	for(int i = num + 1, j; i <= n; ++i) {
		j = tst[i-1] - 'a';
		sum[j] = (sum[j] + invf[i]) % mod;
		for(; t <= q && uu[t].id <= i; ++t) {
			int res = 0, p = uu[t].p;
			for(int k = 0; k <= 26; ++k) {
				res = (res + 1ll * sum[k] * (cnt[k][las[p]]-cnt[k][dfn[p]-1]) % mod) % mod;
			} 
			ans[uu[t].o] = 1ll * res * f[i] % mod;
		}
	}
}
int main() {
 	cin >> n >> q;
	invf[0] = 1; f[0] = 1;
	for(int i = 1; i <= n; ++i) invf[i] = 1ll * inv2 * invf[i-1] % mod, f[i] = 2ll * f[i-1] % mod;
	cin >> s; scanf("%s", tst);
	for(int i = 1; i <= q; ++i) {
		scanf("%d%s", &uu[i].id, name);
		uu[i].p = insert(name); uu[i].o = i;
	}
	sort(uu + 1, uu + 1 + q);
	build();
	for(int x = 1; x <= tot; ++x) ch[fail[x]].push_back(x);
	dfs(0); // get dfn
	gao();
	for(int i = 1; i <= q; ++i) {
		printf("%d\n", (ans[i] + mod) % mod);
	} 
	
	
	/*for(int i = 1; i <= q; ++i) {
		int id = uu[i].id, p = uu[i].p;
		ll res = 0;
		for(int j =0 ;j < num; ++j) {
			res = (res + cnt[j][p] * sum[j][id] % mod) % mod;
		}
		res = res * f[id] % mod;
		printf("%lld\n", (res + mod) % mod);
	}*/
}

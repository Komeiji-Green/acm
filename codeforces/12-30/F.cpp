#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll Pow(ll a, ll k) {
	ll res = 1;
	while(k) {
		if(k&1) res = res * a % mod;
		k >>= 1; a = a * a % mod;
	}
	return res;
}
const int maxn = 500500;
int w[maxn], f[maxn];
int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}
int gao() {
	int k, u, v;
	scanf("%d", &k);
	if(k == 1) {
		scanf("%d", &u);
		int fa = find(u);
		if(w[fa] >= 1) return 0;
		++w[fa];
	} else {
		scanf("%d %d", &u, &v);
		int fu = find(u), fv = find(v);
		if(fu == fv || w[fu] + w[fv] >= 2) return 0;
		w[fu] += w[fv]; f[fv] = fu;
	}
	return  1;
}
int ans[maxn];
int main() {
	int n, m;
	cin >> n >> m;
	for(int i=  1;i <= m; ++i) f[i] = i;
	int cnt = 0;
	for(int i= 1; i<= n; ++i) {
		if(gao()) {
			ans[++cnt]=i;
		}
	}
	ll sum = Pow(2, cnt);
	cout << sum << " " << cnt << endl;
	for(int i= 1; i <= cnt; ++i) {
		printf("%d ", ans[i]);
	}
	cout << endl;
} 

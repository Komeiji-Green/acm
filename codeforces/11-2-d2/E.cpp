#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll f[20], rev[20];
int sz;
bool vis[20];
void gao(ll x) {
	memset(rev, 0, sizeof(rev));
	sz = 0;
	if(!x) return;
	for(sz = 1; sz <= 14 && x >= f[sz]; ++sz);
	memset(vis, 0, sizeof(vis));
	for(int i = sz, cnt; i; --i) {
		cnt = x / f[i - 1];
		for(int j = 1; j <= sz; ++j) {
			if(vis[j]) continue;
			if(cnt == 0) {
				vis[j] = true;
				rev[i] = j;
				break;
			}
			--cnt;
		}
		x = x % f[i - 1];
	}
}

ll pre(ll n) {
	return n * (n + 1) / 2;
}
int main() {
	f[0] = 1;
	for(ll i = 1; i <= 14; ++i) {
		f[i] = i * f[i - 1];
		//printf("%d: %lld\n", i, f[i]);
	}
	ll n, q;
	cin >> n >> q;
	ll sum = 0;
	int op;
	ll l, r, x, ans;
	while(q--) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%lld%lld", &l, &r);
			if(r <= (n - sz)) {
				printf("%lld\n", pre(r) - pre(l - 1));
			} else {
				ans = 0;
				if(l <= (n - sz)) {
					ans += pre(n - sz) - pre(l - 1);
				}
				int m = max(n - sz + 1, l);
				for(int i = m; i <= r; ++i) {
					ans += rev[n - i + 1] + n - sz;
				}
				printf("%lld\n", ans);	
			}
		} else {
			scanf("%lld", &x);
			sum += x;
			gao(sum);
		}
	}
} 

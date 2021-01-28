#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 230000;
const ll mod = 998244353;
int vis[maxn], le[maxn], ri[maxn], sb[maxn], b[maxn];
int main() {
	int T;
	cin >> T;
	int n, k;
	while(T--) {
		scanf("%d %d", &n , &k);
		for(int i = 1,w; i <= n; ++i) {
			scanf("%d", &w);		
			sb[w] = i;
		}
		for(int i = 0; i <= n; ++i) vis[i] = 0;
		for(int i = 1, w; i <= k; ++i) {
			scanf("%d", &w);
			b[i] = sb[w]; vis[b[i]] = true;
		}
		for(int i = 1; i <= n; ++i) {
			le[i] = i - 1;
		}
		for(int i = 1; i <= n; ++i) {
			ri[i] = i + 1;
		}
		ri[n] = 0;
		ll ans = 1;
		for(int i = 1, j, cnt; i <= k; ++i) {
			j = b[i];
			cnt = 0;
			if(le[j] && !vis[le[j]]) ++cnt;
			if(ri[j] && !vis[ri[j]]) ++cnt;
			ans = ans * cnt % mod;
			le[ri[j]] = le[j];
			ri[le[j]] = ri[j];
		}
		printf("%lld\n", ans);
	}
}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 100000007;
const int maxn = (1<<18) + 505;
int bit[33], l[maxn], r[maxn], h[maxn], minv[maxn];
ll dp[maxn], sum[33];
int main() {
	int T;
	cin >> T;
	for(int i = 0; i < 19; ++i) bit[i] = (1<<i);
	while(T--) {
		int m, n;
		scanf("%d %d", &m, &n);
		for(int i = 1; i <= n; ++i) scanf("%d %d", &l[i], &r[i]);
		for(int i = 1, a, b, len; i < bit[17]; ++i) {
			a = i - 1, b = i; len = 0;
			for(int j = m - 1; j >= 0; --j) {
				if((bit[j]&a) != (bit[j]&b)) break;
				++len;
			}
			h[i] = len;
		}
		for(int i = l[1]; i <= r[1]; ++i) dp[i] = i;
		for(int i = r[1] + 1; i <= r[n]; ++i) dp[i] = 0;
		for(int i = 2, bd; i <= n; ++i) {
			bd = h[l[i]];
			minv[l[i]-1]=m; minv[l[i]]=m;
			for(int j = l[i]-2; j >= l[i-1]; --j) minv[j] = min(h[j+1], minv[j+1]);
			for(int j = l[i]+1; j <= r[i]; ++j) minv[j] = min(h[j], minv[j-1]);
			
			for(int j = 0; j <= m; ++j) sum[j] = 0;
			for(int x = l[i]-1; x >= l[i-1]; --x) {
				if(minv[x] >= bd)
					sum[bd] = (sum[bd] + dp[x]) % mod;
				else 
					sum[minv[x]] = (sum[minv[x]] + dp[x]) % mod;
			}
			for(int y = l[i]; y <= r[i]; ++y) {
				if(minv[y] >= bd) {
					dp[y] = 1ll * y * sum[bd] % mod;
				} else {
					dp[y] = 1ll * y * sum[minv[y]] % mod;
				}
			}
			/*
			//ll sum = 0;
			while(x >= l[i-1] && minv[x] >= bd) {
				sum = (sum + dp[x]) % mod;
				--x;
			}
			while(y <= r[i] && minv[y] >= bd) {
				dp[y] = 1ll * y * sum % mod;
				++y;
			}
			// dp clear
			while(x >= l[i-1] && y <= r[i]) {
				if(h[x] > h[y])
			}
			*/
		}
		ll ans = 0;
		for(int i = l[n]; i <= r[n]; ++i) {
			ans = (ans + dp[i]) % mod;
		}
		printf("%lld\n", (ans + mod) % mod);		
	}
}

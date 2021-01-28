#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;

ll dp[5050][5050];
ll c[5050], w[5050];
int main() {
	int n, k, q;
	cin >> n >> k >> q;
	for(int i = 1; i <= n; ++i) dp[i][0] = 1;
	for(int j = 1; j <= k; ++j) {
		for(int i = 1; i <= n; ++i) {
			dp[i][j] = (dp[i-1][j-1] + dp[i+1][j-1])%mod;
		}
	}
	for(int i = 1; i <= n; ++i) {
		w[i] = 0;
		for(int j = 0; j <= k; ++j) {
			w[i] = (w[i] + dp[i][j]*dp[i][k-j]%mod)%mod;
		}
	}
	for(int i =1; i <= n; ++i) scanf("%lld", &c[i]);
	ll sum = 0;
	for(int i = 1; i <= n; ++i) sum = (sum + w[i] * c[i] % mod) % mod;
	int x; ll v;
	while(q--) {
		scanf("%d %lld", &x, &v);
		sum = (sum + w[x] * (v - c[x]) % mod) % mod;
		c[x] = v;
		printf("%lld\n", (sum + mod) % mod);
	}
	
}

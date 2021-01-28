#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;

const int maxn = 10000100;
int inv[maxn], dp[maxn], fc[maxn];

void init(int n) {
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i <= n; ++i) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    fc[0] = 1;
	for(int i = 1; i <= n; ++i) fc[i] = 1ll * i * fc[i-1] % mod;
}
int main() {
	int n, k;
	cin >> n >> k;
	init(n);
	if(k >= n) {
		printf("%d\n", (fc[n]+mod)%mod);
	} else {
		int sum = 0;
		for(int i = 1; i <= k; ++i) {
			dp[i] = 1; sum = (sum + dp[i]) % mod;
		}
		for(int i = k + 1; i <= n; ++i) {
			dp[i] = 1ll * inv[i] * sum % mod;
			sum = (sum - dp[i-k]) % mod;
			sum = (sum + dp[i]) % mod;
		}
		int ans = 1ll * dp[n] * fc[n] % mod;
		printf("%d\n", (ans + mod) % mod);
	}
}

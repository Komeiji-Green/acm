#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;

ll dp[2][105][10005];
ll a[105], b[105];
int main() {
	int n; cin >> n;
	for(int i = 1; i <= n; ++i) scanf("%lld %lld", &a[i], &b[i]);
	for(int d = 0; d <= 1; ++d) 
		for(int i = 0; i <= n; ++i) 
			for(int j = 0; j <= 10000; ++j) 
				dp[d][i][j] = -inf;
	int st = 0;
	dp[st][0][0] = 0;
	for(int i = 1; i <= n; ++i) {
		st ^= 1;
		for(int k = 1; k <= 10000; ++k) dp[st][0][k] = -inf;
		dp[st][0][0] = 0;
		for(int j = 1; j <= n; ++j) {
			for(int k = 0; k <= 10000; ++k) {
				if(k >= a[i]) dp[st][j][k] = max(dp[st^1][j][k], dp[st^1][j-1][k-a[i]] + b[i]);
				else dp[st][j][k] = dp[st^1][j][k];
			}
		}
	}
	ll sum = 0;
	for(int i = 1; i <= n; ++i) sum += b[i];
	for(int j = 1; j <= n; ++j) {
		ll res = 0;
		for(ll k = 0; k <= 10000; ++k) {
			if(dp[st][j][k] >= 0) res = max(res, min(2 * k, dp[st][j][k] + sum));
		}
		printf("%.10f ", res / 2.0);
	}
	printf("\n");
}

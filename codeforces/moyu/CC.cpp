#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;

ll dp[33][2][2];
ll dpx[33], dpy[33], p3[33];
int hx, hy, bit[33];
ll ans, cur;
int main() {
	int T, x, y;
	cin >> T;	
	for(int i = 1; i <= 31; ++i) bit[i] = (1<<(i-1));
	p3[0] = 1; for(int i = 1; i <= 31; ++i) p3[i] = 3ll * p3[i-1]%mod;
	while(T--) {
		scanf("%d%d", &x, &y);
		if(x < y) swap(x, y);
		for(hx = 31; hx >= 1; --hx) if(bit[hx]&x) break;
		for(hy = 31; hy >= 1; --hy) if(bit[hy]&y) break;
		
		// 1 0 0 0 1
		// 0 1 0 0 0
		// 1 x x x x x
		// 0 <=
		// 0 1 0 0 0 1
		dpx[0] = dpy[0] = 1;
		for(int k = 1; k <= 31; ++k) {
			if(bit[k]&x) {
				dpx[k] = (2ll*p3[k-1]+dpx[k-1])%mod;
			} else {
				dpx[k] = 2ll*dpx[k-1]%mod;	
			}
			//printf("dpx: %d %lld\n", k, dpx[k]);
		}
		for(int k = 1; k <= 31; ++k) {
			if(bit[k]&y) {
				dpy[k] = (2ll*p3[k-1]+dpy[k-1])%mod;
			} else {
				dpy[k] = 2ll*dpy[k-1]%mod;	
			}
			//printf("dpy: %d %lld\n", k, dpy[k]);
		}
		
		// 0 1 0
		// 0 <=
		// 0 <=
		// 0 0 1
		dp[0][0][0] = 1;
		for(int k = 1; k <= 31; ++k) {
			if((bit[k]&x)&&(bit[k]&y)) {
				dp[k][0][0] = p3[k-1];
				dp[k][1][0] = dpx[k-1];
				dp[k][0][1] = dpy[k-1];
			} else if((bit[k]&x)&&!(bit[k]&y)) {
				dp[k][0][0] = dpy[k-1];
				dp[k][0][1] = 0;
				dp[k][1][0] = (dp[k-1][0][0]+dp[k-1][0][1]+dp[k-1][1][0])%mod;
			} else if(!(bit[k]&x)&&(bit[k]&y)) {
				dp[k][0][0] = dpx[k-1];
				dp[k][1][0] = 0;
				dp[k][0][1] = (dp[k-1][0][0]+dp[k-1][0][1]+dp[k-1][1][0])%mod;
			} else if(!(bit[k]&x)&&!(bit[k]&y)) {
				dp[k][0][0] = (dp[k-1][0][0]+dp[k-1][0][1]+dp[k-1][1][0])%mod;
				dp[k][0][1] = dp[k][1][0] = 0;
			}
			//printf("%d: 00:%lld 01:%lld 10:%lld\n", k, dp[k][0][0], dp[k][0][1], dp[k][1][0]);
		}
		
		// 1 1 0 0 1 0
		// 0 1 x x x x
		// 0 0 <=
		// 0 0 1 0 0 1
		ans = 0;
		for(int k = 1; k <= 31; ++k) {
			if(k < hx && k < hy) {
				cur = 2ll*p3[k-1]%mod;
			} else if(k < hx && k == hy) {
				cur = dpy[k] - p3[k-1];
			} else if(k < hx && k > hy) {
				cur = dpy[k-1];
			} else if(k == hx) {
				cur = (dp[k][0][1] + dp[k][1][0]) % mod;
			} else {
				cur = 0;
			}
			//printf("test: %d %lld\n", k, cur);
			ans = (ans + k * cur % mod) % mod;
		}
		printf("%lld\n", (ans + mod) % mod);
	}
} 

// 1 0 0 0 1
// 1 0 0 0 1	9 + 5    
// 0 x x x 0       
// 0 1 0 0 0
/*
8 17
dpx: 1 3
dpx: 2 6
dpx: 3 12
dpx: 4 24
dpx: 5 186

dpy: 1 2
dpy: 2 4
dpy: 3 8
dpy: 4 62
dpy: 5 124

 1 0 0 0 1
 0 1 0 0 0

1: 00:1 01:0 10:1
2: 00:2 01:3 10:2
3: 00:7 01:0 10:0
4: 00:12 01:7 10:0
5: 00:62 01:0 10:19

test: 1 2
test: 2 6
test: 3 18
test: 4 35
test: 5 19
303
*/

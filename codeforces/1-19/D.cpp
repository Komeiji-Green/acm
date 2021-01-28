#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
ll a[N];
ll dp[N], minv[N];
int main() {
	int T;
	cin >> T;
	int n;
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%lld",&a[i]);
		ll sum = 0;
		dp[1] = a[1];
		for(int i = 2; i <= n; ++i) {
			dp[i] = a[i] - dp[i-1];
		}
		minv[n]=dp[n];minv[n-1] =dp[n-1];
		for(int i = n - 2; i >= 1; --i) {
			minv[i]=min(dp[i],minv[i+2]);
		}
		bool f = 1;
		for(int i = 1; i < n; ++i) {
			if(dp[i] < 0){
				f=0;break;
			}
		}
		if(dp[n])f=0;
		//for(int i = 1; i <= n; ++i) printf("%lld ", dp[i]);
		//printf("\n");
		if(!f) {
			for(int i = 1; i < n; ++i) {
				ll c = a[i+1]-a[i];
				ll cc = ((n-i)%2) ? -2*c : 2*c;
				if(minv[i+1]-2*c>=0 &&
					dp[i]+c>=0 &&
					(i+2>n||minv[i+2]+2*c>=0) &&
					dp[n]+cc==0) {
						f = 1; break;
					}
				if(dp[i] < 0) break;
			}
		}
		if(f) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
} 

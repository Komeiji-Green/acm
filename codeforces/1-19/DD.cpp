##include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
ll a[N];
ll dp1[N], dp2[N];
int main() {
	int T;
	cin >> T;
	int n;
	while(T--) {
		scanf("%d", &n);
		for(int i =1; i <= n; ++i) scanf("%lld",&a[i]);
		ll sum = 0;
		dp1[1] = 0;
		for(int i = 2; i <= n; ++i) {
			dp1[i] = a[i-1]-dp1[i-1];
		}
		dp2[n] = 0;
		for(int i = n - 1; i >= 1; --i) {
			dp2[i] = a[i+1]-dp2[i+1];
		}
		int cnt = 0;
		bool f = 1;
		for(int i = 1; i < n; ++i) {
			if(a[i] < dp[i] || a[i+1] < dp[i+1]) f=0;
			
		}
	}
} 

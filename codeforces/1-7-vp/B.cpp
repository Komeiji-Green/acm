#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int dp[233][233];
int a[233], b[233];
int main() {
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
		scanf("%d", &m);
		for(int i = 0; i < m; ++i) scanf("%d", &b[i]);
		dp[n][m] = 0;
		for(int i = n; i >= 0; --i) {
			for(int j = m; j >= 0; --j) {
				dp[i][j] = 0;
				if(i < n) dp[i][j] = max(dp[i][j], dp[i+1][j] + a[i]);
				if(j < m) dp[i][j] = max(dp[i][j], dp[i][j+1] + b[j]);
			}
		}
		/*for(int i = 0; i <= n; ++i) {
			for(int j = 0; j <= m; ++j) {
				printf("%d ", dp[i][j]);
			}
			printf("\n");
		}*/
		printf("%d\n", dp[0][0]);
	}
} 

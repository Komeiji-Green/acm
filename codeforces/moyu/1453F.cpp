#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;

const int maxn = 5050;
int a[maxn], dp[maxn][maxn];
/*
int main() {
	int T, n;
	cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		dp[n][n] = 0;
		for(int i = 1; i <= n; ++i) dp[i][i-1]=inf;
		for(int i = n - 1; i >= 1; --i) {
			dp[i][i] = dp[i+1][i+a[i]];
			for(int j = i + 1; j <= n; ++j) dp[i][j] = min(1 + dp[i+1][j], dp[i+1][max(i+a[i], j)]);
		}
		printf("%d\n", dp[1][1]);
	}
}*/

int C[maxn], n;
void add(int x, int v) {
	for(int i = x; i <= n; i += (i & (-i))) {
		C[i] += v;
	}
}
int query(int x) {
	int res = 0;
	for(int i = x; i; i -= (i & (-i))) {
		res += C[i];
	}
	return res;
}
int main() {
	int T, ri;
	cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for(int i = 0; i <= n; ++i) C[i] = 0;
		dp[n][n+1] = 1; add(n, 1);
		a[n] = 1;
		for(int i = n - 1; i >= 1; --i) {
		 	ri = i + a[i];
			for(int j = i + 1; j <= ri; ++j) {
				if(j + a[j] > ri && dp[j][ri+1]) {
					dp[i][j] = dp[j][ri+1] + query(j - 1) + 1;
					//dp[i][j] = max(dp[i], dp[j] + query(j - 1) + 1);
				} else {
					dp[i][j] = 0;
				}
			}
			for(int j = ri - 1; j >= i + 1; --j) dp[i][j] = max(dp[i][j + 1], dp[i][j]);
			add(i + a[i], 1);
		}
		//for(int i = 1; i <= n; ++i) printf("%d ", dp[i]);
		//printf("\n");
		printf("%d\n", n - dp[1][2]);
	}
}

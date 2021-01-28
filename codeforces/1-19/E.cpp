#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p[233333];
int main() {
	int T;
	cin >> T;
	while(T--) {
		int n;
		scanf("%d", &n);
		int mid = (n + 1) / 2;
		if(n > 2) {
			for(int i = 1; i < n; ++i) p[i] = i + 1;
			p[mid] = 1; p[1] = mid + 1; p[n] = 2;
		} else {
			p[1] = 2, p[2] = 1;
		}
		ll ans = 0;
		for(ll i = 2; i < n; ++i) ans += max((i-1)*(i-1), (n-i)*(n-i));
		ans += 1ll * (n - 1) * (n - 1);
		printf("%lld\n", ans);
		for(int i = 1; i <= n; ++i) printf("%d ", p[i]);
		printf("\n");
		printf("%d\n", n - 1);
		for(int i = 2; i <= mid; ++i) {
			printf("%d %d\n", i, n);
		}
		for(int i = mid + 1; i < n; ++i) {
			printf("%d %d\n", i, 1);
		}
		printf("%d %d\n", 1, n);
	}
} 

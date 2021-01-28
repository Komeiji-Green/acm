#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
char r[maxn], b[maxn];
int main() {
	int T;
	int n;
		scanf("%d", &n);
		if(n % 2 == 0) {
			ll m = n / 2;
			ll ans = (m + 1)*(m+1);
			printf("%lld\n", ans);
		} else {
			ll m = n / 2;
			ll p = n - m;
			ll ans = 2 * (m + 1) * (p + 1);
			printf("%lld\n", ans);
		}
} 

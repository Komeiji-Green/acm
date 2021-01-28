#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 233333;
ll a[maxn], dn[maxn], up[maxn];
int main() {
	int T, n;
	cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n ;++i) scanf("%lld", &a[i]);
		for(int i = 1; i < n; ++i) {
			if(a[i] > a[i - 1]) {
				dn[i] = 0;
				up[i] = a[i] - a[i - 1];
			} else {
				dn[i] = a[i - 1] - a[i];
				up[i] = 0;
			}
		}
		ll sum = 0;
		for(int i = 1; i < n; ++i) {
			sum += dn[i];
		}
		if(sum <= a[0]) printf("YES\n");
		else printf("NO\n");
	}
}

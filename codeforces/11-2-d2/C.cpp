#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 233333;
const ll INF = 0x3f3f3f3f3f3f3f3f;
struct DD {
	ll a, b;
	bool operator<(const DD& rhs) {
		return a > rhs.a;
	}
} dd[maxn];
ll pre[maxn];
int main() {
	int T, n;
	cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%lld", &dd[i].a);
		for(int i = 1; i <= n; ++i) scanf("%lld", &dd[i].b);
		sort(dd + 1, dd + n + 1);
		pre[0] = 0;
		for(int i = 1; i <= n; ++i) {
			pre[i] = pre[i - 1] + dd[i].b;
		}
		dd[n + 1].a = 0;
		ll ans = INF, cur;
		for(int i = 0; i <= n; ++i) {
			cur = max(dd[i + 1].a, pre[i]);
			ans = min(ans, cur);
		}
		printf("%lld\n", ans);
	}
}

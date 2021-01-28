#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll INF = 0x3f3f3f3f3f3f3f3f;

const int maxk = 5050;
struct DDD{
	ll x, y;
	bool operator<(const DDD& b) {
		return x < b.x;
	}
} uu[maxk];
ll a[maxk], b[maxk], mm[maxk];
int main() {
	int T;
	cin >> T;
	ll n; int k;
	ll ans, cur;
	while(T--) {
		scanf("%lld %d", &n, &k);
		for(int i = 0; i < k; ++i) scanf("%lld", &a[i]);
		for(int i = 0; i < k; ++i) scanf("%lld", &b[i]);
		sort(a, a + k);
		sort(b,b+k);
		ans = INF;
		for(int i =0; i < k; ++i) {
			for(int j = i, d = 0; d < k; j = (j+1)%k, d++) {
				if(b[j] >= a[d]) {
				uu[d].x = b[j]-a[d];
				uu[d].y = n - uu[d].x;
				} else {
					uu[d].y = a[d]-b[j];
					uu[d].x = n - uu[d].y;
				}
			}
			sort(uu, uu + k);
			mm[k] = 0;
			for(int j = k-1; j >=0;--j) {
				mm[j] = max(mm[j+1], uu[j].y);
			}
			ll maxx = 0, maxy;
			cur = INF;
			for(int j = 0; j <= k; ++j) {
				maxy = mm[j];
				cur = min(cur, min(maxy*2ll+maxx, maxy + maxx*2ll));
				maxx = uu[j].x;
			}
			ans = min(ans, cur);
		}
		printf("%lld\n", ans);
	}
} 

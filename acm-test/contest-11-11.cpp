#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll x, y;
ll p[100];
int x0[100], cx0, x1[100], cx1, y0[100], cy0, y1[100], cy1;
int main() {
	for(ll i = 0; i < 63; ++i) {
		p[i] = (1ll << i);
		//printf("%lld\n", p[i]);
	}
	int T;
	cin >> T;
	ll ans = 0;
	int cas = 0;
	while(T--) {
		++cas;
		scanf("%lld%lld", &x, &y);
		cx0 = cx1 = cy0 = cy1 = 0;
		for(ll i = 0; i < 63; ++i) {
			//printf("%lld\n", p[i]);
			if(p[i]&x) {
				if(i&1) x1[cx1++] = i;
				else x0[cx0++] = i;
			}
			if(p[i]&y) {
				if(i&1) y1[cy1++] = i;
				else y0[cy0++] = i;
			}
		}
		if(cx0 != cy0 || cx1 != cy1) {
			ans = -1;
		} else {
			ans = 0;
			//printf("%d %d %d %d\n", cx0, cy0, cx1, cy1);
			for(int i = 0; i < cx0; ++i) {
				ans += abs(x0[i] - y0[i]) / 2;
			}
			for(int i = 0; i < cx1; ++i) {
				ans += abs(x1[i] - y1[i]) / 2;
			}
		}
		printf("Case %d: %lld\n", cas, ans);
	}
} 

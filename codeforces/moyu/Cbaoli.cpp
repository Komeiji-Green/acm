#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ans = 0;
int main() {
	int T;
	int x, y, m, hb;
	cin >> T;
	while(T--) {
		scanf("%d %d", &x ,&y);
		ans = 0;
		for(int i = 0; i <= x; ++i) for(int j = 0; j <= y; ++j) {
			if((i&j)==0){
				m = i + j;
				for(hb = 10; hb >= 0; --hb) {
					if((1<<hb)&m)break;
				}
				++hb;
				ans += hb;
			}
		}
		printf("%lld\n", ans);
	}
}

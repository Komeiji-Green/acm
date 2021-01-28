#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
char s[maxn];
ll seg[maxn];
int main() {
	int T;
	cin >> T;
	ll a, b;
	while(T--) {
		scanf("%lld%lld", &a, &b);
		scanf("%s", s);
		ll last = 0;
		int tot = 0;
		for(int i = 0; s[i]; ++i) {
			if(s[i] == '0') {
				++last;
			} else {
				if(i == 0 || i > 0 && s[i-1] == '0') {
					seg[tot++] = last;
					last = 0;
				}
			}
		}
		ll ans = 0;
		if(!tot) ans = 0;
		else {
			ans = a;
			for(int i = 1; i < tot; ++i) {
				ans += min(seg[i] * b, a);
			}
		}
		printf("%lld\n", ans);
	}
}

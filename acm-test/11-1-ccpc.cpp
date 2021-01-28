#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 233333;
const ll mod = 1e9 + 7;

// ¿ìËÙÃÝ ¼ÆËã a^k % p
ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

struct P {
	ll a, x;
	bool operator<(const P& b) {
		return a < b.a; 
	}
} p[maxn];
ll f[maxn];
int main() {
	f[0] = 1;
	for(ll i = 1; i <= 60; ++i) {
		f[i] = 2ll * f[i - 1] % mod;
	}
	int T, n;
	cin >> T;
	int cas = 0;
	while(T--) {
		++cas;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%lld %lld", &p[i].a, &p[i].x);
		}
		sort(p + 1, p + n + 1);
		ll cur = 1, ans = 1, x = 0;
		p[0].a = 0;
		ll d;
		for(int i = 1, j; i <= n; i = j) {
			x = p[i].x;
			cur = p[i].x;
			for(j = i + 1; j <= n && (d = p[j].a - p[j - 1].a) <= 50 && (1ll << d) <= x; ++j) {
				x = x / (1ll << d) + p[j].x;
				cur = (cur + Pow(2, p[j].a - p[i].a, mod) * p[j].x % mod) % mod;
			}
			//printf("%d %d: %lld\n", i, j, cur);
			ans = ans * (cur + 1) % mod;
		}
		printf("Case #%d: %lld\n", cas, (ans + mod) % mod);
	}
} 

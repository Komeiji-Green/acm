#include<bits/stdc++.h>
using namespace std;
const int maxn = 233333;
typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;
ll a[maxn];
ll gcd(ll a, ll b) {
	return a == 0 ? b : gcd(b % a, a);
}

int n;
ll mgcd(int le, int ri) {
	if(le > ri) return 0;
	if(le == ri) {
		return a[le];
	}
	int mid = le + ((ri - le) >> 1);
	ll x = mgcd(le, mid);
	ll y = mgcd(mid + 1, ri);
	return gcd(x, y);
}

// 素因数分解 
ll p[maxn], l[maxn], cnt = 0;
void Fact(ll x) {
    cnt = 0;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            p[++cnt] = i; l[cnt] = 0;
            while(x % i == 0) {
                x /= i; ++l[cnt];
            }
        }
    }
    if(x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[++cnt] = x; l[cnt] = 1;
    }
}
int main() {
	int T;
	cin >> T;
	
	ll ans = 0, cur = 0;
	int cas = 0;
	while(T--) {
		++cas;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) scanf("%lld", &a[i]);
		sort(a, a + n);
		for(int i = 1; i < n; ++i) a[i] = a[i] - a[0];
	
		ll g = mgcd(1, n - 1);
		if(g == 0) {
			if(a[0] <= 1) ans = 2 - a[0];
			else ans = 0;
		} else if(g == 1) {
			ans = -1;
		} else {
			ans = INF;
			Fact(g);
			for(int i = 1; i <= cnt; ++i) {
				if(a[0] % p[i] == 0) cur = 0;
				else cur = p[i] - a[0] % p[i];
				ans = min(ans, cur);
			}
		}
		printf("Case %d: %lld\n", cas, ans);
	}
}

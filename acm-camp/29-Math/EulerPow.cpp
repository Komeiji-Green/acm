#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

int p[maxn], l[maxn], cnt = 0;
void Fact(int x) {
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

int euler(int n) {
    Fact(n);
    int ans = n;
    for(int i = 1; i <= cnt; ++i) {
        ans /= p[i];
        ans *= p[i] -1;
    }
    return ans;
}
ll a[maxn];
ll phi[2005];
int main() {
	int n, m, cur, h = 0;
	cin >> n >> m;
	cur = m;
	phi[h] = cur;
	while(cur > 1) {
		++h;
		cur = euler(cur);
		phi[h] = cur;
	}
	for(int i = 0; i <= h; ++i) printf("%lld\n", phi[i]);
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	int q;
	cin >> q;
	int le, ri;
	ll ans = 1;
	while(q--) {
		scanf("%d%d", &le, &ri);
		if(le + h <= ri) ri = le + h - 1;
		if(le > ri) {
			printf("0\n");
		} else {
			ans = 1;
			for(int i = ri; i >= le; --i) {
				ans = (Pow(a[i], ans < phi[i + 1 - le] ? ans : (ans % phi[i + 1 - le] + phi[i + 1 - le]), phi[i - le]) + phi[i - le]) % phi[i - le];
				
			}
			ans %= m;
			printf("%lld\n", (ans + m) % m);
		}
	}
}

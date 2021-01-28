#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

const int maxn = 1005;
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

int main() {
	srand(time(NULL));
	ll mod = 33332;
	ll phi = euler(mod);
	int T = 3000000;
	while(T--) {
		ll a = rand() % 33332 + 1;
		ll b = rand() % (2 * phi) + 1;
		ll p1 = (Pow(a, b % phi + phi, mod) + mod) % mod;
		ll p2 = (Pow(a, b, mod) + mod) % mod;
		//if(b > 2) printf("11\n");
		if(p1 != p2) {
			printf("-1\n");
			printf("a: %lld, b: %lld, mod: %lld, phi: %lld\n", a, b, mod, phi);
		}
	}
}

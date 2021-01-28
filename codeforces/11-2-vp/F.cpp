#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

const int maxn = 233333;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛求积性函数
int mu[maxn];
void Sieve(int n) {
    isnt[1] = true;
    mu[1] = 1;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
            // d[i] = 2; q[i] = 1;
            // D[i] = i + 1; q[i] = 1;
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                mu[x] = 0;
                // d[x] = d[i] / (q[i] + 1) * (q[i] + 2), q[x] = q[i] + 1;
                // D[x] = D[i] / (prime[j] ^ (q[i] + 1) - 1) * (prime[j] ^ (q[i] + 2) - 1), q[x] = q[i] + 1;
                break;
            } else {
                mu[x] = -mu[i];
                // d[x] = 2 * d[i], q[x] = 1;
                // D[x] = (prime[j] + 1) * D[i], q[x] = 1;
            }
        }
    }
}

ll a[maxn], f[maxn];
vector<ll> bei[maxn];
int main() {
	Sieve(200000);
	ll n;
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld%lld", &a[i], &f[i]);
	}
	for(ll i = 1, j; i <= n; ++i) {
		for(j = 1; j * j < a[i]; ++j) {
			if(a[i] % j == 0) {
				bei[j].push_back(i);
				bei[a[i] / j].push_back(i);
			}
		}
		if(j * j == a[i]) bei[j].push_back(i);
	}
	ll ans = 0, cur;
	ll sum, sum2, sz = 0, ssz;
	for(int i = 1; i <= 100000; ++i) {
		sum = 0, sum2 = 0, sz = 0;
		for(auto id : bei[i]) {
			sz += f[id];
			sum = (sum + a[id] * f[id] % mod) % mod;
			sum2 = (sum2 + (a[id] * a[id] % mod) * f[id] % mod) % mod;
		}
		if(sz >= 3) {
			ssz = sz % mod;
			cur = (((sum * sum % mod) * ssz % mod + (ssz - 2) * sum2 % mod) % mod) * Pow(2, sz - 3, mod) % mod;
			ans = (ans + cur * mu[i]) % mod;
			//printf("%lld: %d\n", cur, mu[i]);
		} else if(sz == 2) {
			cur = sum * sum % mod;
			ans = (ans + sum * sum * mu[i] % mod) % mod;
			//printf("%lld: %d\n", cur, mu[i]);
		}
	}
	printf("%lld\n", (ans + mod) % mod);
} 

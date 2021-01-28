#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7, inv3 = 333333336;
const int maxn = 1000005; // O(sqrt(n)) 

bool isnt[maxn];
ll prime[maxn], num, sp1[maxn], sp2[maxn]; // 素数和，素数平方和
void Sieve(ll n) {
	isnt[1] = true; num = 0; sp1[num] = sp2[num] = 0;
	for(int i = 2; i <= n; ++i) {
		if(!isnt[i]) {
			prime[++num] = i;
			// 0. 前k个素数处取值之和 
			sp1[num] = (sp1[num-1] + i) % mod;
			sp2[num] = (sp2[num-1] + 1ll * i * i % mod) % mod;
		}
		for(int j = 1; j <= num; ++j) {
			ll x = i * prime[j];
			if(x > n) break;
			isnt[x] = 1;
			if(i % prime[j] == 0) break;
		}
	}
}
ll n, sq, tot, w[maxn], id1[maxn], id2[maxn], g1[maxn], g2[maxn]; 

inline ll f(ll x) { // 3. f(p^c)
	ll xx = x % mod;
	return xx * (xx - 1) % mod;
}

ll S(ll x, int y) {
	if(prime[y] >= x) return 0;
	ll k = (x <= sq ? id1[x] : id2[n / x]);
	ll res = ((g2[k] - g1[k] + mod) - (sp2[y] - sp1[y] + mod)) % mod; // 2. 各项合并 
	for(int i = y + 1; i <= num && prime[i] * prime[i] <= x; ++i) {
		ll pc = prime[i];
		for(int c = 1; pc <= x; pc = pc * prime[i], ++c) {
			res = (res + f(pc) * (S(x / pc, i) + (c != 1)) % mod) % mod;
		}
	}
	return res % mod;
}

int main() {
	scanf("%lld", &n);
	sq = sqrt(n+0.5);
	Sieve(sq);
	
	tot = 0;
	for(ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		w[++tot] = n / i;
		// 1. 不筛任何素数时的g值：从2到n的累加 
		g1[tot] = w[tot]%mod;
		g2[tot] = (((g1[tot] * (g1[tot] + 1) / 2) % mod) * (2*g1[tot]+1) % mod) * inv3 % mod;
		g2[tot] = (g2[tot]-1) % mod; 
		g1[tot] = (g1[tot] * (g1[tot] + 1) / 2 % mod - 1) % mod;
		if(w[tot] <= sq) id1[w[tot]] = tot;
		else id2[n / w[tot]] = tot;
	}
	
	for(int i = 1; i <= num; ++i) {
		for(int j = 1; j <= tot && prime[i] * prime[i] <= w[j]; ++j) {
			ll k = (w[j] / prime[i]) <= sq ? id1[w[j] / prime[i]] : id2[n / (w[j] / prime[i])];
			g1[j] = (g1[j] - prime[i] * ((g1[k] - sp1[i-1]) % mod) % mod) % mod;
			g2[j] = (g2[j] - (prime[i] * prime[i] % mod) * ((g2[k] - sp2[i-1]) % mod) % mod) % mod;
		}
	}
	
	ll ans = (S(n, 0) + 1) % mod;
	printf("%lld\n", (ans + mod) % mod);
} 

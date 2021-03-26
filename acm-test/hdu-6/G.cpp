#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
inline void add(ll &x, ll y) {
    x += y;
    (x >= mod) && (x -= mod);
    (x < 0) && (x += mod);
}   

ll Pow(ll a, ll k) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % mod;
        k >>= 1; a = a * a % mod;
    }
    return ans;
}

const int maxn = 233333 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;
int mu[maxn];
void Sieve(int n) {
    isnt[1] = true;
    mu[1] = 1;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= cnt; j++) {
            ll x = 1ll * i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                mu[x] = 0;
                break;
            } else {
                mu[x] = -mu[i];
            }
        }
    }
}
ll po[maxn], ppo[maxn];
ll S[maxn], mp[maxn], fp[maxn];
ll Q[maxn];

int main() {
    int T;
    ll k, x, kx, nn = 200000;
    cin >> T >> k >> x;
    kx = k * x;

    Sieve(200001);
    S[0] = 0;
    for(int i = 1; i <= nn; ++i) po[i] = Pow(i, k);
    for(int i = 1; i <= nn; ++i) S[i] = (S[i-1] + po[i]) % mod;
    for(int i = 1; i <= nn; ++i) S[i] = Pow(S[i], x);

    for(int i = 1; i <= nn; ++i) ppo[i] = Pow(i, kx);

    for(int i = 1; i <= nn; ++i) mp[i] = ppo[i]*mu[i];
    //for(int i = 2; i <= nn; ++i) mp[i] = (mp[i] + mp[i-1]) % mod;

    for(int i = 1; i <= nn; ++i) {
        for(int j = i; j <= nn; j += i) {
            ll val = mp[i]*S[j/i]%mod;
            Q[j] = (Q[j] + val) % mod; //add(Q[j], val);
            if(j + i <= nn) Q[j+i] = (Q[j+i] - val) % mod;//add(Q[j+i], -val);
        }
    }
    for(int i = 1; i <= nn; ++i) add(Q[i], Q[i-1]);
    for(int i = 1; i <= nn; ++i) fp[i] = abs(mu[i])*ppo[i]*(ll)i%mod;
    for(int i = 2; i <= nn; ++i) fp[i] = (fp[i] + fp[i-1]) % mod;

    while(T--) {
        int n;
        ll ans = 0;
        scanf("%d", &n);
        for(int i = 1, j, d; i <= n; i = j + 1) {
            d = n / i; j = n / d;
            //ans = (ans + (fp[j]-fp[i-1])*Q[n/i]%mod) % mod;
            add(ans, (fp[j]-fp[i-1])*Q[n/i]%mod);
        }
        printf("%lld\n", (ans+mod)%mod);
    }
    sizeof(size_t);
}
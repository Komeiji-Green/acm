#include <bits/stdc++.h>
#include<vector>
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

ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
// ax + by = (a, b)
ll exgcd(ll a,ll b,ll &x,ll &y) {
    if(!b){ x = 1; y = 0; return a;}
    ll gcd = exgcd(b, a % b, x, y);
    ll tp = x; x = y; y = tp - a / b * y;
    return gcd;
}

// 扩欧求逆元
ll INV(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

void Fact(ll x, vector<ll>& fact) {
    for(ll i = 2; i * i <= x; ++i) {
        if(x % i == 0) {
            fact.push_back(i);
            while(x % i == 0) x /= i; 
        }
    }
    if(x != 1) fact.push_back(x);
}
// 素数 p 的原根
ll generator(ll p) {
    ll phi = p - 1;
    vector<ll> fact;
    Fact(phi, fact);
    for (ll res = 2; res <= p; ++res) {
        bool ok = true;
        for (ll factor : fact) {
            if (Pow(res, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return res;
    }
    return -1;
}

// x: a^x = b (mod p)
ll BSGS(ll a, ll b, ll p) {
    ll k = 0, D = 1, tmp;
    while((tmp = gcd(a, p / D)) != 1) {
        ++k;
        D *= tmp;
    }
    vector<ll> res;
    for(ll i = 0; i < k; ++i) {
        if((Pow(a, i, p) - b) % p == 0) return i;
    }
    ll md = p / D, ak = Pow(a, k, md);
    ll sq = (ll)(sqrt(md + .0)) + 1;
    vector<pair<ll, ll> > dec(sq);
    if(b % D == 0) {
        b = (b % md) * INV(ak, md) % md;
        for(ll i = 1, key; i <= sq; ++i) {
            key = (Pow(a, i * sq, md) % md + md) % md;
            dec[i - 1] = make_pair(key, i);
        }
        sort(dec.begin(), dec.end());
        for(ll j = sq, key; j >= 1; --j) {
            key = (b % md * Pow(a, j, md) % md + md) % md;
            auto it = lower_bound(dec.begin(), dec.end(), make_pair(key, 0ll));
            if(it != dec.end() && (*it).first == key) {
                return (*it).second * sq - j;
            }
        }
        sort(res.begin(), res.end());
        res.erase(unique(res.begin(), res.end()), res.end());
        if(res.empty()) return -1;
        return res[0];
    }
    return -1;
}

int main() {
    ll a, b, p;
    while(scanf("%lld%lld%lld", &a, &p, &b) != EOF && a) {
        ll ans = BSGS(a, b, p);
        if(ans == -1) printf("No Solution\n");
        else printf("%lld\n", ans);
    }
}
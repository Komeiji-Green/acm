#include<bits/stdc++.h>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<set>
#include<vector>
using namespace std;

#define rint register int

typedef unsigned long long ull;
typedef long long ll;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

const ll mod = 998244353;
const int N = 333333;
ull p[N], q = 19260817;
ll f[N], rf[N], inv[N];

char s[N];

ull preh[N];
void prehash(char *s) {
    preh[0] = 0;
    for(int i = 0; s[i]; ++i) {
        preh[i + 1] = preh[i] * q + (ull)s[i];
    }
}
ull hsh(int l, int r) {
    return preh[r] - preh[l] * p[r - l];
}

ull sub[2 * N], sub1[N], sub2[N];
int cnt[2 * N];


int s1, s2;
ll gao(int d, int n) {
    ll ans = 0;
    int m = n / d;
    if(n % d == 0) {
        map<ull, int> mp_cnt;
        //vector<ull> sub(n / d);
        for(int i = 0, j = 0; i < n; i += d, ++j) {
            sub[j] = hsh(i, i + d);
            mp_cnt[sub[j]]++;
        }
        ans = f[m];
        for(auto it : mp_cnt) {
            ans = ans * rf[it.second] % mod;
        }
        return ans;
    } else {
        //unordered_map<ull, int> id;
        set<ull> vis;
        //vector<ull> sub(2 * m), sub1(m), sub2(m);
        for(int i = d, j = 0; i < n; i += d, ++j) {
            sub1[j] = sub[j] = hsh(i - d, i);
        }
        for(int i = n % d, j = 0; i < n; i += d, ++j) {
            sub2[j] = sub[j + m] = hsh(i, i + d);
        }
        sort(sub, sub + 2 * m);
        int sz = unique(sub, sub + 2 * m) - sub;
        for(int i = 0; i < m; ++i) {
            sub1[i] = lower_bound(sub, sub + sz, sub1[i]) - sub;
            sub2[i] = lower_bound(sub, sub + sz, sub2[i]) - sub;
        }

        //vector<int> cnt(sz, 0);
        for(int i = 0; i < sz; ++i) cnt[i] = 0;
        for(int i = 0; i < m; ++i) {
            ++cnt[sub2[i]];
        }
        ull hs = 0;
        ll cur = f[m];
        for(int i = 0; i < sz; ++i) {
            hs += 1ull * p[i] * cnt[i];
            cur = cur * rf[cnt[i]] % mod;
        }
        ans = (ans + cur) % mod;
        vis.insert(hs);
        for(rint i = 0; i < m; ++i) {
            //cout << "sb1: " << sub1[i] << " sb2: " << sub2[i] << endl;
            s1 = sub1[i], s2 = sub2[i];
            hs += p[s1] - p[s2];
            cur = cur * cnt[s2] % mod;
            --cnt[s2];
            ++cnt[s1];
            cur = cur * inv[cnt[s1]] % mod;
            if(!vis.emplace(hs).second) continue;
            ans = (ans + cur) % mod;
        }
        return ans;
    }
}

int main() {
    inv[0] = 0;
    inv[1] = 1;
    for(ll i = 2; i < N; ++i) {
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    }
    p[0] = 1ull;
    for(ull i = 1; i < N; ++i) {
        p[i] = p[i - 1] * q;
    }
    f[0] = 1; rf[0] = 1;
    for(ll i = 1; i < N; ++i) {
        f[i] = f[i - 1] * i % mod;
        rf[i] = rf[i - 1] * inv[i] % mod;
    }
    int T, len;
    ll sum;
    cin >> T;

    int cas = 0;
    while(T--) {
        ++cas;
        scanf("%s", s);
        len = strlen(s);
        prehash(s);
        sum = 0;
        for(int i = 1; i <= len; ++i) {
            sum = (sum + gao(i, len)) % mod;
        }
        printf("Case #%d: %lld\n", cas, (sum + mod) % mod);
    }
}
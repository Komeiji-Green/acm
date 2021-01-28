#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 慢速乘
ll mul(ll a, ll b, ll mod) {
    ll res=0;
    while(b > 0) {
        if(b & 1) res = (res+a)%mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }


ll x1, x2, y2;
bool check(ll a, ll b) {
    if(y2 == 0 && b != 0) return false;
    if(y2 == 0) {
        if(!x1 && !x2) return a == 0;
        return a % gcd(x1, x2) == 0;
    }
    if(b % y2) return false;
    ll k = b / y2, t = a - k * x2;
    return x1 == 0 && t == 0 || x1 != 0 && t % x1 == 0;
}

void exgcd(ll &a, ll &b, ll &c, ll &d) {
    if(!b) return;
    c = c - (a / b) * d;
    a = a - (a / b) * b;
    exgcd(b, a, d, c);
}

void add(ll x, ll y) {
    exgcd(y2, y, x2, x);
    if(y2 == 0) swap(y2, y), swap(x2, x);
    x1 = gcd(x1, x);
    if(x1 < 0) x1 = -x1;
    if(x1) x2 = x2 % x1;
    if(y2 < 0) y2 = -y2, x2 = -x2;
}

int main() {
    int T, q, op;
    ll x, y, w;
    cin >> T;
    int cas = 0;
    while(T--) {
        ++cas;
        x1 = x2 = y2 = 0;
        ll sum = 0;
        scanf("%d", &q);
        while(q--) {
            scanf("%d%lld%lld", &op, &x, &y);
            if(op == 1) {
                add(x, y);
                //printf("x1: %lld x2: %lld y2: %lld\n", x1, x2, y2);
            } else {
                scanf("%lld", &w);
                bool flag;
                if(flag = check(x, y)) sum += w;
                //printf("flag: %d\n", flag);
            }
        }
        printf("Case #%d: %lld\n", cas, sum);
    }
}
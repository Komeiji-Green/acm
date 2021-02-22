
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll c;
// ax + by = c, 没开ll
// 扩展欧几里得算法, 有解当且仅当gcd(a, b) | c
// a, b 不全为 0, 返回gcd(a, b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) { x = c / a; y = 0; return a; }
    ll ans = exgcd(b, a % b, x, y);
    ll xx = x; // xx == x'
    x = y, y = xx - a / b * y;
    return ans;
}

const int maxn = 1005;
int p[maxn], l[maxn], cnt2 = 0;
void Fact(ll x) {
    cnt2 = 0;
    for(ll i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            p[++cnt2] = i; l[cnt2] = 0;
            while(x % i == 0) {
                x /= i; ++l[cnt2];
            }
        }
    }
    if(x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[++cnt2] = x; l[cnt2] = 1;
    }
}

int main() {
    ll n;
    cin >> n;
    Fact(n);
    if(cnt2 == 1) {
        printf("NO\n");
    } else {
        printf("YES\n");
        ll a = 1, b;
        for(int i = 1; i <= l[1]; ++i) a *= p[1];
        b = n / a;
        ll x, y;
        c = n - 1;
        exgcd(a, b, x, y);
        y = ((y % a) + a) % a; // y > 0
        x = (c - b * y) / a;
        printf("2\n");
        printf("%lld %lld\n", x, b);
        printf("%lld %lld\n", y, a); 
    }

}
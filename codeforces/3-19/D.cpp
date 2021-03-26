#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 20000007;
bool isnt[maxn];
int prime[maxn], num[maxn];
int cnt = 0;

// 线性筛法 [1, n] 内素数
void Prime(int n) {
    isnt[1] = true; 
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i, num[i] = 1;
        for (int j = 1; j <= cnt; j++) {
            if (1ll * i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            num[i * prime[j]] = num[i] + 1;
            if (i % prime[j] == 0) {
                num[i * prime[j]]--;
                break;
            }
        }
    }
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int po[1000], c, d, x;

// c * n - d * m == x;
// n = lcm(a, b), m = gcd(a, b)
int chk(int m) {
    ll tmp = 0ll+x+1ll*d*m;
    if(tmp%c) return 0;
    ll n = tmp / c;
    if(n%m) return 0;
    return po[num[n / m]];
}
int main() {
    Prime(20000001);
    po[0] = 1; for(int i = 1; i <= 10; ++i) po[i] = 2 * po[i-1];
    int T; cin >> T;
    int g;
    ll ans = 0, xx, yy;
    while(T--) {
        scanf("%d %d %d", &c, &d, &x);
        g = gcd(c, d); // c*xx + d*yy = x
        ans = 0;
        if(x % g == 0) { // m | x
            int i = 1;
            for(; i * i < x; ++i) { 
                if(x % i == 0) {
                    ans += chk(i);
                    ans += chk(x / i);
                }
            }
            if(i * i == x) ans += chk(i);
            printf("%lld\n", ans);
        } else {
            printf("0\n");
        }
    }
}
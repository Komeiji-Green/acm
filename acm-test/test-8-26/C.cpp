#include <iostream>
#include <ctime>
#include <cstdio>
using namespace std;
typedef long long ll;

const int maxn = 1000000 + 5;

// 慢速乘
ll mul(ll a,ll b,ll mod)
{
    ll res=0;
    while(b > 0)
    {
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}


//int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }


// ax + by = (a, b)
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){ x = 1; y = 0; return a;}
    ll gcd = exgcd(b, a % b, x, y);
    ll tp = x;
    x = y; y = tp - a / b * y;
    return gcd;
}


// UPD 8.26

// 扩展中国剩余定理，用途：解同余方程组，模可以非质数，可以不两两互质
ll ai[maxn], bi[maxn];  // x ≡ ai(mod bi)
void excrt(ll& LCM, ll& ANS, int n)
{
    ll x, y, k;
    ll M = bi[1], ans = ai[1]; //第一个方程的解特判
    for (int i = 2; i <= n; i++)
    {
        ll a = M, b = bi[i], c = (ai[i] - ans % b + b) % b; //ax ≡ c(mod b)
        ll gcd = exgcd(a, b, x, y), bg = b / gcd;
        if (c % gcd != 0) {
            ANS = -1;
            return; // 判断是否无解
        }

        x = c / gcd * x % bg;
        ans += x * M; // 更新前k个方程组的答案
        M *= bg;      // M为前k个m的lcm
        ans = (ans % M + M) % M;
    }
    ANS = (ans % M + M) % M;
    LCM = M;
}


int main()
{
    int T;
    cin >> T;
    while(T--) {
        ll n;
        int m;
        cin >> n >> m;
        for(int i = 1; i <= m; i++) {
            scanf("%lld", &bi[i]);
        }
        for(int i = 1; i <= m; i++) {
            scanf("%lld", &ai[i]);
        }
        ll lcm, ans;
        excrt(lcm, ans, m);
        if(ans == -1 || ans > n) {
            printf("%d\n", 0);
        } else {
            ll num = (n - ans) / lcm + 1;
            if(ans == 0) num--;
            printf("%lld\n", num);
            //printf("%lld %lld\n", ans, lcm);
        }
    }
}
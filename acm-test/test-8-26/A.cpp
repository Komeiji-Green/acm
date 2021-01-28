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
    ll a, b, c, d;
    bi[1] = 23;
    bi[2] = 28;
    bi[3] = 33;
    int cas = 0;
    while(scanf("%lld%lld%lld%lld", &a, &b, &c, &d) != EOF && a != -1) {
        cas++;
        ai[1] = a, ai[2] = b, ai[3] = c;
        ll lcm, ans;
        excrt(lcm, ans, 3);
        //printf("yes: %lld %lld\n", lcm, ans);
        ll num;
        if((d - ans) % lcm == 0) {
            num = lcm;
            //printf("%lld\n", lcm);
        } else if(ans > d) {
            num = ans - d;
            //printf("%lld\n", ans - d);
        } else {
            num = ((ans - d) % lcm + lcm) % lcm;
            //num = lcm - num;
            //printf("%lld\n", num);
        }
        printf("Case %d: the next triple peak occurs in %lld days.\n", cas, num);
    }
}
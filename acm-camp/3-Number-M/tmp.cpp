#include <cstdio>
#include <iostream>
#define LL long long
using namespace std;
const LL MAXN = 1e6 + 10;
LL K, C[MAXN], M[MAXN], x, y;
LL gcd(LL a, LL b)
{
    return b == 0 ? a : gcd(b, a % b);
}
LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    LL r = exgcd(b, a % b, x, y), tmp;
    tmp = x;
    x = y;
    y = tmp - (a / b) * y;
    return r;
}
LL inv(LL a, LL b)
{
    LL r = exgcd(a, b, x, y);
    while (x < 0)
        x += b;
    return x;
}
int main()
{
#ifdef WIN32
    freopen("a.in", "r", stdin);
#else
#endif
    while (~scanf("%lld", &K))
    {
        for (LL i = 1; i <= K; i++)
            scanf("%lld%lld", &M[i], &C[i]);
        bool flag = 1;
        for (LL i = 2; i <= K; i++)
        {
            LL M1 = M[i - 1], M2 = M[i], C2 = C[i], C1 = C[i - 1], T = gcd(M1, M2);
            if ((C2 - C1) % T != 0)
            {
                flag = 0;
                break;
            }
            M[i] = (M1 * M2) / T;
            C[i] = (inv(M1 / T, M2 / T) * (C2 - C1) / T) % (M2 / T) * M1 + C1;
            C[i] = (C[i] % M[i] + M[i]) % M[i];
        }
        printf("%lld\n", flag ? C[K] : -1);
    }
    return 0;
}

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long lt;

lt read()
{
    lt f = 1, x = 0;
    char ss = getchar();
    while (ss < '0' || ss > '9')
    {
        if (ss == '-')
            f = -1;
        ss = getchar();
    }
    while (ss >= '0' && ss <= '9')
    {
        x = x * 10 + ss - '0';
        ss = getchar();
    }
    return f * x;
}

const int maxn = 100010;
int n;
lt ai[maxn], bi[maxn];

lt mul(lt a, lt b, lt mod)
{
    lt res = 0;
    while (b > 0)
    {
        if (b & 1)
            res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

lt exgcd(lt a, lt b, lt &x, lt &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    lt gcd = exgcd(b, a % b, x, y);
    lt tp = x;
    x = y;
    y = tp - a / b * y;
    return gcd;
}

lt excrt()
{
    lt x, y, k;
    lt M = bi[1], ans = ai[1]; //第一个方程的解特判
    for (int i = 2; i <= n; i++)
    {
        lt a = M, b = bi[i], c = (ai[i] - ans % b + b) % b; //ax≡c(mod b)
        lt gcd = exgcd(a, b, x, y), bg = b / gcd;
        if (c % gcd != 0)
            return -1; //判断是否无解，然而这题其实不用

        x = mul(x, c / gcd, bg);
        ans += x * M; //更新前k个方程组的答案
        M *= bg;      //M为前k个m的lcm
        ans = (ans % M + M) % M;
    }
    return (ans % M + M) % M;
}

int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        bi[i] = read(), ai[i] = read();
    printf("%lld", excrt());
    return 0;
}

int n;
ll ai[maxn], bi[maxn];
ll excrt()
{
    ll x, y, k;
    ll M = bi[1], ans = ai[1]; //第一个方程的解特判
    for (int i = 2; i <= n; i++)
    {
        ll a = M, b = bi[i], c = (ai[i] - ans % b + b) % b; //ax≡c(mod b)
        ll gcd = exgcd(a, b, x, y), bg = b / gcd;
        if (c % gcd != 0)
            return -1; //判断是否无解，然而这题其实不用

        x = mul(x, c / gcd, bg);
        ans += x * M; //更新前k个方程组的答案
        M *= bg;      //M为前k个m的lcm
        ans = (ans % M + M) % M;
    }
    return (ans % M + M) % M;
}

int js;
ll pri[100];
ll Pollard_Rho(ll n)
{
    ll x = rand() % n, y = x, c = rand() % n, QvQ = 2;
    int i = 1;
    while (1)
    {
        ++i, x = (qmul(x, x, n) + c) % n; //生成伪随机数
        if (y == x)
            return 1; //兔子追上了乌龟
        ll d = gcd((y - x + n) % n, n);
        if (d > 1)
            return d; //注意，有可能在某个c意义下，d一直都是n
        if (i == QvQ)
            y = x, QvQ <<= 1; //移动乌龟
    }
}
void getpri(ll n)
{
    if (n == 1)
        return;
    if (Miller_Rabin(n))
    {
        pri[++js] = n;
        return;
    } //如果是质因子
    ll p = n;
    while (p == n)
        p = Pollard_Rho(n);
    getpri(n / p), getpri(p); //递归处理
}
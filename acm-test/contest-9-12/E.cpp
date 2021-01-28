#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;

const int maxn = (1<<23) + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

const ll ii = 1ll * 998244353 * 998244353;

// 线性筛法 [1, n] 内素数
void Prime(int n)
{
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

// 慢速乘
ll mul(ll a,ll b,ll mod)
{
    ll res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

// 快速幂 计算 a^k % p
// a <= 1e9, k <= 1e9
ll Pow(ll a, ll k, ll p) 
{
    ll ans = 1;
    while(k) {
        if(k & 1) ans = mul(ans, a, p);
        k >>= 1; a = mul(a, a, p);
    }
    return ans;
}

bool Miller_Rabin(ll x) //判断素数，事先打好素数表
{
    int s = 0; ll t = x - 1;
    if (x == 2) return true;
    if (x < 2 || !(x & 1)) return false; 
    while (!(t & 1)) {   //将x分解成(2^s)*t的样子
        s++; t >>= 1;
    }
    ll k;
    for (int i = 1; i <= 20 && prime[i] < x; ++i) //随便选一个素数进行测试
    {
        ll a = prime[i];
        ll b = Pow(a, t, x); //先算出a^t
        for (int j = 1; j <= s; ++j) { //然后进行s次平方
            k = mul(b, b, x);        //求b的平方
            if (k == 1 && b != 1 && b != x - 1) //用二次探测判断
                return false;
            b = k;
        }
        if (b != 1)
            return false; //用费马小定律判断
    }
    return true; //如果进行多次测试都是对的，那么x就很有可能是素数
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int js;
ll pri[100];
ll Pollard_Rho(ll n)
{
    ll x = rand() % n, y = x, c = rand() % n, QvQ = 2;
    int i = 1;
    while (1)
    {
        ++i, x = (mul(x, x, n) + c) % n; //生成伪随机数
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
    if (n == 1) return;
    if (Miller_Rabin(n)) { pri[++js] = n; return; } // 如果是质因子
    ll p = n;
    while (p == n)
        p = Pollard_Rho(n);
    getpri(n / p), getpri(p); //递归处理
}

const int N = 105000;
ll a[N];
ll b[N];

int main() {
    Prime(1<<23);
    int T;
    cin >> T;
    while(T--) {
        int n;
        ll X, Y;
        scanf("%d %lld %lld", &n, &X, &Y);
        a[0] = Y;
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        js = 0;
        getpri(X);

        map<ll, int> num;
        for(int i = 1; i <= js; i++) {
            num[pri[i]]++;
        }
        ll minv = INF;
        for(auto it : num) {
            ll p = (it).first;
            int k = (it).second;
            /*printf("fact:\n");
            printf("%lld %d\n", p, k);*/
            for(int i = 0; i <= n; i++) {
                ll ans = 0;
                ll po = p;
                while(po <= a[i]) {
                    ans += a[i] / po;
                    po *= p;
                }
                b[i] = ans;
            }
            ll res = b[0];
            for(int i = 1; i <= n; i++) {
                res -= b[i];
            }
            minv = min(minv, res / k);
        }
        printf("%lld\n", minv);
    }
}
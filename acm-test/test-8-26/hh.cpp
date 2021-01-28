#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef long long ll;

const int S = 8;

const ll INF = 0x7fffffffffffffff;

// 慢速乘
ll mul(ll a,ll b,ll mod)
{
    ll res = 0;
    a %= mod; b %= mod;
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
    a %= p;
    while(k) {
        if(k & 1) ans = mul(ans, a, p);
        k >>= 1; a = mul(a, a, p);
    }
    return ans;
}

ll gcd(ll a, ll b) {
    ll t;
    while(b) {
        t = a;
        a = b;
        b = t % b;
    }
    if(a >= 0) return a;
    else return -a;
}

bool check(ll a, ll n, ll x, ll t) {
    ll ret = Pow(a, x, n);
    ll last = ret;
    for(int i = 1; i <= t; i++) {
        ret = mul(ret, ret, n);
        if(ret == 1 && last != 1 && last != n - 1) 
            return true;
        last = ret;
    }
    if(ret != 1) return true;
    else return false;
}

ll prime[50] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 27, 29, 31, 37, 41, 43, 47 };

bool Miller_Rabin(ll x) //判断素数，事先打好素数表
{
    int s = 0; ll t = x - 1;
    if (x == 2) return true;
    if (x < 2 || !(x & 1)) return false; 
    while (!(t & 1)) {   //将x分解成(2^s)*t的样子
        s++; t >>= 1;
    }
    ll k;
    for (int i = 1; i <= 15 && prime[i] < x; ++i) //随便选一个素数进行测试
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

ll factor[100];
int tol;

ll pollard_rho(ll x, ll c) {
    ll i = 1, k = 2;
    srand(time(NULL));
    ll x0 = rand() % (x - 1) + 1;
    ll y = x0;
    while(1) {
        i++;
        x0 = (mul(x0, x0, x) + c) % x;
        ll d = gcd(y - x0, x);
        if(d != 1 && d != x) return d;
        if(y == x0) return x;
        if(i == k) {y = x0; k += k;}
    }
}

void findfac(ll n) {
    if(n == 1) return;
    if(Miller_Rabin(n)) {
        factor[++tol] = n;
        return;
    }
    ll p = n;
    ll c = 1;
    while(p >= n && c <= n) p = pollard_rho(p, c++);
    findfac(p);
    findfac(n / p);
}

const int N = 105000;
ll a[N];
ll b[N];

int main() {
    //Prime(1<<23);
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
        tol = 0;
        findfac(X);

        map<ll, int> num;
        for(int i = 1; i <= tol; i++) {
            num[factor[i]]++;
        }
        ll minv = INF;
        for(auto it : num) {
            ll p = (it).first;
            int k = (it).second;
            /*printf("fact:\n");
            printf("%lld %d\n", p, k);*/
            for(int i = 0; i <= n; i++) {
                ll ans = 0;
                ll part = 0;
                ll po = 1;
                do {
                    po *= p;
                    part = a[i] / po;
                    ans += part;
                } while(part >= p);
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

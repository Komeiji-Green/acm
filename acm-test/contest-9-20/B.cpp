#include <iostream>
#include <ctime>
using namespace std;
typedef long long ll;

const int maxn = 1000000 + 5;
bool isnt[maxn];
ll prime[maxn];
int cnt = 0;
ll sum = 1;
ll mod = 998244353;

// 线性筛法 [1, n] 内素数
void Prime(ll n, ll m, ll p)
{
    isnt[1] = true;
    cnt = 0;
    for (ll i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            ll x = i * prime[j];
            if(x <= n) isnt[x] = 1;
            if(x > m) break;
            sum += x;
            //sum %= mod;
            //printf("x: %lld\n", x);
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    ll m;
    scanf("%lld", &m);
    m++;

    Prime(1000000, m, 998244353);

    ll cp = 0;
    for(int i = 1; i <= cnt; i++) {
        if(prime[i] <= m) cp += prime[i];
    }
    printf("sumpri: %lld\n", cp);
    ll ans = (1 + m) * m / 2;
    ans -= sum;
    printf("%lld\n", ans);
    ans = ((m - 1) * (m + 2) / 2 + ans - 4) % 998244353;
    printf("%lld\n", ans);
}
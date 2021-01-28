#include <cmath>
#include <iostream>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll c;
// 扩展欧几里得算法, 有解当且仅当gcd(a, b) | c
// a, b 不全为 0, 返回gcd(a, b)
// 没开ll
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = c / a;
        y = 0;
        return a;
    }
    ll ans = exgcd(b, a % b, x, y);
    ll xx = x; // xx == x'
    x = y, y = xx - a / b * y;
    return ans;
}

//输入只包括一行5个整数x，y，m，n，L，
//其中x≠y < 2000000000，0 < m、n < 2000000000，0 < L < 2100000000。
int main()
{
    ll x, y, m, n, L;
    cin >> x >> y >> m >> n >> L;
    ll t, s;
    c = y - x;
    if (m != n)
    {
        ll d = exgcd(m - n, L, t, s);
        if (c % d)
            cout << "Impossible" << endl;
        else
        {
            ll mm = L / d;
            if(mm < 0) mm = -mm;
            ll ans = t % mm;
            if (ans < 0)
                ans = mm + ans;
            cout << ans << endl;
        }
    }
    else cout << "Impossible" << endl;
}
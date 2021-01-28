#include <iostream>
using namespace std;

/*
2
4 6 13
2 3 1

4 6 5
2 2 3
*/

typedef long long ll;

void division(ll a, ll b, ll &q, ll &r)
{
    if (a >= 0)
    {
        q = a / b;
        r = a % b;
    }
    else if (a < 0)
    {
        q = a / b - 1;
        r = b + a % b;
    }
}

int main()
{
    ll l, r, m;
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        scanf("%lld %lld %lld", &l, &r, &m);

        // 1 <= l <= a, b, c <= r
        // n*a + b - c == m, n >= 1
        //      m + c - b == n * a >= a
        //      m - r + l <= m + c - b <= m + r - l
        //          let q2 = (m + r - l) / a;
        //          let r2 = (m + r - l) % a;
        //      if exist
        //             let q2 * a == m + c - b;
        //      b - c == m - q2 * a
        //      l + d <= b == c + d <= r + d
        //          l <= b <= r
        //      if(d > 0) b == l + d
        //      else b == r + d
        for (ll a = l; a <= r; a++)
        {
            ll q1, r1, q2, r2;
            division(m + l - r, a, q1, r1);
            division(m - l + r, a, q2, r2);

            bool ok = q2 > 0 && (q1 < q2 || q1 == q2 && r1 == 0);
            if (!ok)
                continue;
            ll d = m - q2 * a;
            ll b = d > 0 ? l + d : r + d;
            ll c = b - d;
            printf("%lld %lld %lld\n", a, b, c);
            break;
        }
    }
}
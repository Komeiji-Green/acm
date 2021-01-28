#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;
const ll INF = 0x7fffffffffffffff;
int a[maxn];
ll b[maxn];  // 前缀和
ll sum[maxn]; // 局部和：目标

ll diff_change[maxn];   // 变化量差分
ll change[maxn];    // 变化量

int n, r;
ll k;

// 要保证，在进行至多k次操作以内，就能使min(b[i]) >= ans,
// 也即全体b[i] >= ans, 这样无需刻意去求最小值。
bool check(ll ans)
{
    memset(change, 0, sizeof(ll) * (n + 1));
    memset(diff_change, 0, sizeof(ll) * (n + 1));
    ll cnt = 0; // 消耗
    for (int i = r; i < n; i++)
    {
        int le = i - r;
        int ri = min(n - 1, i + r);

        ll d = ans - sum[le] - change[le];
        if (d <= 0) d = 0;

        cnt += d;
        if(cnt > k) return false;

        diff_change[le] += d;
        diff_change[ri + 1] -= d;

        change[le] += d;
        change[le + 1] = change[le] + diff_change[le + 1];
    }

    for(int i = n - r + 1; i < n; i++) {
        change[i] = change[i - 1] + diff_change[i]; 
    }


    ll d = ans - sum[n - 1] - change[n - 1];
    if(d > 0)
        cnt += d;
    if(cnt > k) return false;
    return true;
}

int main()
{
    cin >> n >> r >> k;

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    b[0] = a[0];
    for (int i = 1; i < n; i++)
    {
        b[i] += b[i - 1] + a[i];
    }

    for (int i = 0; i < n; i++)
    {
        int le = max(0, i - r);
        int ri = min(n - 1, i + r);
        if (le == 0)
            sum[i] = b[ri];
        else
            sum[i] = b[ri] - b[le - 1];
    }

    ll min = 0;
    ll max = b[n - 1] + k;
    ll mid = (min + max + 1) >> 1;
    while (min < max)
    {
        if(check(mid)) {
            min = mid;
        } else {
            max = mid - 1;
        }
        mid = (min + max + 1) >> 1;
    }
    cout << mid << endl;
}
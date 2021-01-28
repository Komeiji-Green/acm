/*
2
4 3
5 0
1 4
2 2

5 3
5 2
4 2
3 1

14
16
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;
const int maxn = 100000 + 5;

pair<int, int> v[maxn];
ll R_a[maxn];

ll sum[maxn];

// total = ai+(xi−1)⋅bi

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int m, n;
        cin >> n >> m;
        int a, b;
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d", &a, &b);
            v[i] = pair<int, int>(a, b);
        }

        sort(v, v + m); // 从小到大

        memset(sum, 0, m * sizeof(ll));
        memset(R_a, 0, m * sizeof(ll));
        
        R_a[m] = 0;
        for (int i = m - 1; i >= 0; i--)
        {
            R_a[i] = R_a[i + 1] + v[i].first; 
        }

        for (int i = 0; i < m; i++)
        {
            int cnt = n;
            pair<int, int> key(v[i].second, 0);
            int idx = lower_bound(v, v + m, key) - v;

            if ((m - idx) >= n)
                idx = m - n;

            sum[i] += R_a[idx];

            cnt = n - (m - idx);
            if (cnt <= 0)
                continue;

            if (i < idx)
            {
                sum[i] += v[i].first;
                cnt--;
            }
            
            sum[i] += (ll)v[i].second * (ll)cnt;
        }

        ll max = 0;
        for (int i = 0; i < m; i++)
        {
            if (sum[i] > max)
                max = sum[i];
        }
        cout << max << endl;
    }
}
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

const int maxn = 100000 + 100;

int a[maxn];
// 若严格小于mid 的数量 大于等于 m + 1 / 2, 则 max = mid - 1
// 若小于等于mid 的数量 严格小于 m + 1 / 2, 则 min = mid + 1
// 否则， 找到了中位数

ll m;
int n;

int check(int mid) {
    ll cnt1 = 0;
    ll cnt2 = 0;
    for(int i = 0; i < n; i++) {
        cnt1 += lower_bound(a, a + n, a[i] + mid) - a - i - 1;
        cnt2 += upper_bound(a, a + n, a[i] + mid) - a - i - 1;
    }
    if(cnt1 >= ((m + 1) / 2)) return 1;
    else if(cnt2 < ((m + 1) / 2)) return -1;
    else return 0;
}

int main()
{
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }

        sort(a, a + n);

        m = 1ll * n * (n - 1) / 2;

        ll min = 0;
        ll max = a[n - 1] - a[0];
        ll mid = (min + max) >> 1;
        int c;
        while(min < max) {
            if((c = check(mid)) == 1) {
                max = mid - 1;
            } else if (c == -1) {
                min = mid + 1;
            } else break;
            mid = (min + max) >> 1;
        }
        cout << mid << endl;

    }
}
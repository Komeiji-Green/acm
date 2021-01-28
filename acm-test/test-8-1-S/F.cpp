#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;

const int maxn = 200000 + 5;

ll a[maxn];
ll aa[maxn];
int b[maxn];
ll t[maxn];

int n, k;

priority_queue<pair<ll, int> > que; // 存活时间与脚标


bool check(ll x) {
    memcpy(aa, a, sizeof(ll) * n);
    priority_queue<pair<ll, int> > q(que);
    for (int t = 0; t < k; t++) {
        if (-q.top().first < t) return false;
        int idx = q.top().second;
        aa[idx] += x;

        pair<ll, int> u(-(aa[idx] / b[idx]), idx);
        q.pop();
        q.push(u);
    }
    return true;
}



int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        t[i] = a[i] / (1ll * b[i]); // t 秒后还活着, t + 1 秒后GG
        que.push(make_pair(-t[i], i));
    }
    ll max = 2 * 1e12;
    ll min = 0;
    ll mid = (min + max) >> 1;
    while (min < max) {
        if (check(mid)) {
            max = mid;
        }
        else {
            min = mid + 1;
        }
        mid = (min + max) >> 1;
    }
    if (check(mid))
        cout << mid << endl;
    else
        cout << -1 << endl;
}
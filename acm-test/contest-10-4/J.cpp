#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;

int n;
const int maxn = 233333;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll C[maxn];
void add(int x, ll v) {
    for(int i = x; i <= n; i += i & (-i)) {
        C[i] += v;
    }
}
ll query(int x) {
    ll ans = 0;
    for(int i = x; i > 0; i -= i & (-i)) {
        ans += C[i];
    }
    return ans;
}

ll a[maxn];

bool cmp(ll a, ll b) {
    return a > b;
}

ll dp[maxn];
int main() {
    cin >> n;
    for(int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }
    /*n = 100000;
    for(int i = 0; i < n; ++i) {
        a[i] = 1ll * 100 * (n - i);
    }
    a[1] = 10000000000;*/
    sort(a, a + n, cmp);

    /*ll last = 0;
    for(int i = 2; i <= n; ++i) {
        add(i-1, a[i] - last);
        last = a[i];
    }*/
    
    dp[1] = 0;
    for(int i = 2; i <= n; ++i) {
        if(i & 1) {
            dp[i] = dp[(i-1) / 2] + 1;
        } else {
            dp[i] = dp[i>>1] + 1;
        }
    }

    ll cnt = 0;
    ll h = a[0] - a[1];
    int idx = 1;
    while((idx+1) < n && a[idx + 1] == a[idx]) ++idx;
    if(idx == 1) {
        ++idx;
        cnt += a[1] - a[2];
    }
    while(1) {
        ll k = dp[idx];
        ll times = (idx + 1 < n) ? a[idx] - a[idx+1] : INF;
        ll t = h / k;
        if(t < times) {
            cnt += t * (dp[idx] + 1);
            h -= k * t;
            cnt += h;
            break;
        } else {
            cnt += times * (dp[idx] + 1);
            h -= k * times;
            ++idx;
        }
    }
    printf("%lld\n", cnt);
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f;
const int N = 150007, M = 200007;

ll a[5][N], tmp[N], dp[2][N], link[N];
vector<int> li[4][N];

void solve(int r, ll *x, int n, ll *y, int m) {
    for(int i = 1; i <= m; ++i) tmp[i] = y[i];
    sort(tmp + 1, tmp + m + 1);
    ll res;
    for(int i = 1; i <= n; ++i) {
        int sz = li[r][i].size();
        for(int j = 0; j < sz; ++j) {
            link[j + 1] = y[li[r][i][j]];
        }
        sort(link + 1, link + sz + 1);
        bool f = 0;
        int j = 1;
        for(j = 1; j <= sz; ++j) {
            if(link[j] != tmp[j]) {
                f = 1;
                res = tmp[j]; break;
            }
        }
        if(j <= m) {
            f = 1; res = tmp[j];
        }
        if(!f) x[i] = INF;
        else x[i] = res + a[r][i];
    }
}

int main() {
    int num[5];
    cin >> num[1] >> num[2] >> num[3] >> num[4];
    for(int i = 1; i <= num[1]; ++i) scanf("%lld", &a[1][i]);
    for(int i = 1; i <= num[2]; ++i) scanf("%lld", &a[2][i]);
    for(int i = 1; i <= num[3]; ++i) scanf("%lld", &a[3][i]);
    for(int i = 1; i <= num[4]; ++i) scanf("%lld", &a[4][i]);
    for(int j = 1; j <= 3; ++j) {
        int m; cin >> m;
        for(int i = 1, x, y; i <= m; ++i) {
            scanf("%d %d", &x, &y);
            li[j][x].push_back(y);
        }
    }
    int st = 0;
    for(int i = 1; i <= num[4]; ++i) dp[st][i] = a[4][i];
    for(int j = 3; j >= 1; --j) {
        solve(j, dp[st^1], num[j], dp[st], num[j+1]);
        st ^= 1;
    }
    ll ans = INF;
    for(int i = 1; i <= num[1]; ++i) {
        ans = min(ans, dp[st][i]);
    }
    if(ans == INF) {
        printf("-1\n");
    } else {
        printf("%lld\n", ans);
    }
}
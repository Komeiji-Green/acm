#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

const int maxn = 105;
ll dp[2][maxn][maxn * (maxn + 1) / 2];    
// 假设过程从第i回合开始，从第i回合开始起及往后，攻击了j次，攻击次数所在绝对脚标之和为k
// 开滚动
ll a[maxn], b[maxn], c[maxn];

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i] >> b[i] >> c[i];
        int pos = 0;
        memset(dp[pos], -1, sizeof(dp[pos]));
        dp[pos][1][n] = a[n];   // 最后一次一定攻击
        pos^= 1;

        ll u, v;
        for(int i = n - 1; i > 0; i--, pos ^= 1) {
            for(int j = 0; j <= n; j++) {
                for(int k = 0; k <= (n + 1) * n / 2; k++) {
                    u = (j >= 1 && k >= i ? dp[pos^1][j - 1][k - i] : -1ll);
                    v = dp[pos^1][j][k];
                    dp[pos][j][k] = 
                max((u < 0 ? -1 : u + a[i]), 
                    (v < 0 ? -1 : v + max(1ll * c[i] * j, (k >= j * i ? 1ll * (k - j * i) * b[i] : 0))));
                }
            }
        }
        ll ans = 0;
        pos^=1;
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k <= (n + 1) * n / 2; k++)
                ans = max(dp[pos][j][k], ans);
        }
        cout << ans << endl;
        
    }
}
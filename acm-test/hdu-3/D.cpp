#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn], pre[maxn], link[maxn], dp[maxn];
int main() {
    int T, n, p;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &p);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        pre[0] = 0;
        for(int i = 1; i<=n;++i) pre[i] = (pre[i-1] + a[i])%p;
        map<int,int> mp;
        for(int i=0; i <= n; ++i) {
            if(!mp.count(pre[i])) {
                link[i] = 0;
            } else {
                link[i] = mp[pre[i]];
            }
            mp[pre[i]] = i;
        }
        dp[0] = 0;
        int ans = 0;
        for(int i = 1; i <= n; ++i) {
            int j = link[i];
            dp[i] = dp[i-1];
            if((pre[i]-pre[j])%p==0) dp[i] = max(dp[i], dp[j] + 1);
        }
        printf("%d\n", dp[n]);

        
    }
}
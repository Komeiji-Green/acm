#include<iostream>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<map>
using namespace std;
typedef long long ll;

const int maxn = 300000 + 100;
const int mod = 9901;

int C[maxn];
int dp[maxn];
ll a[maxn];
ll temp[maxn];

int sz;

void add(int x, int val) {
    for(int i = x; i <= sz; i += (i & (-i))) {
        C[i] += val;
        C[i] %= mod;
    }
}

int query(int x) {
    int ans = 0;
    for(int i = x; i > 0; i -= (i & (-i))) {
        ans += C[i];
        ans %= mod;
    }
    return ans;
}

int main()
{
    ll d; int n;
    while(scanf("%d", &n) != EOF) {
        cin >> d;
        for(int i = 1; i <= n; i++)
            scanf("%lld", &a[i]);

        // 离散化
        map<ll, int> hso;
        
        int j = 0;
        for(int i = 1; i <= n; i++) {
            temp[i] = a[i];
        }
        sort(temp + 1, temp + n + 1);
        int idx = unique(temp + 1, temp + n + 1) - temp;
        
        sz = n;

        // dp, 线段树
        dp[0] = dp[1] = 0;
        memset(C, 0, sizeof(C));

        for(int i = 1; i <= n; i++) {
            int l = lower_bound(temp + 1, temp + idx, a[i] - d) - temp; 
            int r = upper_bound(temp + 1, temp + idx, a[i] + d) - temp;
            int pos = lower_bound(temp + 1, temp + idx, a[i]) - temp;
            dp[i] = query(r - 1) - query(l - 1);
            add(pos, (dp[i] + 1) % mod);
        }
        int ans = 0;
        for(int i = 1; i <= n; i++)
            ans = (ans + dp[i]) % mod;
        cout << (ans < 0 ? ans + mod : ans) << endl;
    }
}
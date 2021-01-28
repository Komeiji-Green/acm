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
            temp[j++] = a[i];
            temp[j++] = a[i] - d;
            temp[j++] = a[i] + d;
        }
        sort(temp, temp + j);
        int idx = unique(temp, temp + j) - temp;
        

        for(int i = 0; i < idx; i++) {
            hso[temp[i]] = i + 1;
        }
        sz = idx + 100;

        // dp, 线段树
        dp[0] = dp[1] = 0;
        memset(C, 0, sizeof(C));

        for(int i = 1; i <= n; i++) {
            int l = hso[a[i] - d]; 
            int r = hso[a[i] + d];
            dp[i] = query(r) - query(l - 1);
            add(hso[a[i]], (dp[i] + 1) % mod);
        }
        int ans = 0;
        for(int i = 1; i <= n; i++)
            ans = (ans + dp[i]) % mod;
        cout << (ans < 0 ? ans + mod : ans) << endl;
    }
}
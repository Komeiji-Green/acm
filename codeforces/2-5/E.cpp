#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 533333;

int dp[maxn], a[maxn];
int le[maxn], ri[maxn], cnt[maxn];
vector<int> vec[maxn];
int main() {
    int n; cin >> n;
    for(int i =1; i<= n; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) {
        if(!le[a[i]]) le[a[i]] = i;
        ri[a[i]] = i;
        cnt[a[i]]++;
        vec[a[i]].push_back(i);
    }
    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        if(i == ri[a[i]]) {
            dp[i] = max(dp[i-1], dp[le[a[i]]-1] + cnt[a[i]]);
        } else {
            dp[i] = dp[i-1];
        }
    }
    int maxv = 0;
    for(int i = 1; i <= n; ++i) {
        int col = a[i];
        if(i != ri[col]) continue;
        int sz = vec[col].size();
        for(int j = 0; j < sz; ++j) {
            int pos = vec[col][j];
            maxv = max(maxv, dp[pos-1] + sz - j);
        }
    }
    printf("%d\n", n - maxv);
}
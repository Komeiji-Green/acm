
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1000007;
int n;
int v[maxn], dp[maxn];

struct node {
    int x;
    ll len;
} a[maxn];
int main() {
    int q;
    cin >> q;
    n = 1000001;
    char op[4];
    int x, j;
    ll len, res, sum; int ans;
    for(int i = 1; i <= q; ++i) {
        scanf("%s", op);
        if(op[0] == '+') {
            scanf("%d %lld", &x, &len);
            a[i].x = x; a[i].len = len;
            v[x] = len;
        } else if(op[0] == '-') {
            scanf("%d", &j);
            x = a[j].x; len = a[j].len;
            v[x] = 0;
        } else {
            scanf("%d", &x);
            dp[0] = 0;
            for(j = 1; j <= x; ++j) {
                dp[j] = max(dp[j-1], j) + v[j]; 
            }
            ans = dp[x] <= x ? 0 : dp[x] - x;
            printf("%d\n", ans);
        }
    }

}
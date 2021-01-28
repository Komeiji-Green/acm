#include<bits/stdc++.h>
using namespace std;

const int maxn = 30 * 233333;
int tr[maxn][2], tot;

int dp[maxn];
void dfs(int x) {
    if(tr[x][0]) dfs(tr[x][0]);
    if(tr[x][1]) dfs(tr[x][1]);
    int aa = (tr[x][0] ? 1 : 0) + dp[tr[x][1]];
    int bb = (tr[x][1] ? 1 : 0) + dp[tr[x][0]];
    //printf("%d")
    dp[x] = max(max(aa, bb), 1); 
}
int a[maxn];
int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) {
        int q = 0;
        for(int j = 30, d; j >= 0; --j) {
            d = ((1<<j) & (a[i])) ? 1 : 0;
            if(!tr[q][d]) tr[q][d] = ++tot;
            q = tr[q][d];
        }
    }
    dfs(0);
    printf("%d\n", n - dp[0]);
    /*for(int i = 0; i <= tot; ++i) {
        printf("%d ", dp[i]);
    }
    cout << endl;*/
}
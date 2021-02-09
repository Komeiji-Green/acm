#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn], dp[maxn][2], col[maxn][2];

int cnt[maxn];
int le, ri;
int main() {
    int n;
    cin >> n;
    for(int i = 1; i<= n; ++i) scanf("%d", &a[i]);
    int tot = 1; cnt[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(a[i] == a[tot]) cnt[tot]++;
        else {
            ++tot;
            a[tot] = a[i]; cnt[tot] = 1;
        }
    }
    int pre = 0;
    int ans = 0;
    for(int i = 1; i <= tot; ++i) {
        if(a[i] == pre) {
            ans++; pre = a[i];
        } else if(cnt[i] > 1) {
            ans += 2;
            pre = a[i];
        } else {
            ans++;
            pre = a[i-1];
        }
    }
    printf("%d\n", ans);
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn], dp[maxn][2], col[maxn][2], b[maxn];

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
    int m = 0, t2 = 0;
    for(int i = 1; i <= tot; ++i) {
        if(cnt[i] > 1) b[++m] = a[i];
    }
    b[0] = 0;
    for(int i = 1; i <= m; ++i) {
        if(b[i] == b[t2]) continue;
        else {
            ++t2;
            b[t2] = b[i];
        }
    }

    printf("%d\n", tot + t2);
}
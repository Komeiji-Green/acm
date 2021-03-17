#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
int a[N], cnt[N];
int main() {
    int T, n, m;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= m; ++i) cnt[i-1] = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            cnt[a[i]%m]++;
        }
        int ans = 0, x, y;
        for(int i = 0; i <= m - i; ++i) {
            if(i == 0 || i == m - i) {
                if(cnt[i]) ++ans;
            } else {
                x = cnt[i], y = cnt[m-i];
                if(x && y) {
                    int d = abs(x-y);
                    if(d <= 1) ++ans;
                    else {
                        ans += d;
                    }
                } else {
                    ans += max(x, y);
                }
            }
        }
        
        printf("%d\n", ans);
    

    }
}
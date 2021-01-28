#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 233333;
ll w[maxn], m, hm;

int ans[maxn], num = 0;

int main() {
    int T;
    cin >> T;
    int n;
    while(T--) {
        scanf("%d%lld", &n, &m);
        hm = (m + 1) / 2;
        for(int i = 1; i <= n; ++i) scanf("%lld", &w[i]);
        int tot = 0;
        bool flag = false;
        for(int i = 1; i <= n; ++i) {
            if(w[i] <= m && w[i] >= hm) {
                flag = true;
                printf("1\n%d\n", i);
                break;
            }
        }
        if(flag) continue;
        ll sum = 0;
        num = 0;
        for(int i = 1; i <= n; ++i) {
            if(w[i] < hm) {
                sum += w[i];
                ans[++num] = i;
                if(sum >= hm && sum <= m) break;
            }
        }
        if(sum >= hm && sum <= m) {
            printf("%d\n", num);
            for(int i = 1; i <= num; ++i) printf("%d ", ans[i]);
            printf("\n");
        } else {
            printf("-1\n");
        }
    }
}
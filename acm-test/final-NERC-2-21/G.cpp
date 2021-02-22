#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int inf = 0x3f3f3f3f;
int a[10];
int main() {
    int T, k;
    cin >> T;
    while(T--) {
        scanf("%d", &k);
        int d = 0, ans = inf;
        for(int i = 0; i < 7; ++i) {
            scanf("%d", &a[i]);
            if(a[i]) ++d;
        }
        for(int i = 0, j; i < 7; ++i) {
            int cur = 0, len = 0;
            for(j = i; j < 7; ++j) {
                if(a[j]) ++cur;
                if(cur == k) break;
            }
            if(cur == k) ans = min(ans, j - i + 1);
            else {
                len = j - i;
                int res = k - cur; // res > 0
                len += ((res - 1) / d) * 7;
                res -= ((res - 1) / d) * d;
                for(j = 0; j < 7 && res; ++j) {
                    if(a[j]) --res;
                }
                len += j;
                ans = min(ans, len);
            }
        }
        printf("%d\n", ans);
    }
}
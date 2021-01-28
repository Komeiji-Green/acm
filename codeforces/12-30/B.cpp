#include<bits/stdc++.h>
using namespace std;

const int maxn = 233333;
int a[maxn];
int main() {
    int T, n;
    cin >>  T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        a[0] = 0;
        int ans = 0, cur = 0, num = 0;
        for(int i = 1; i <= n; ++i) {
            ++num;
            if(a[i] != a[i-1]) ++cur;
            if(i == n || a[i] + 1 < a[i + 1]) {
                if(cur < num) ans += cur + 1;
                else ans += cur;
                cur = 0; num = 0;
            }
        }
        printf("%d\n", ans);
    }
}
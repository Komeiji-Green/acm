#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 333333;
char s[maxn];
int p[maxn];
int ans[maxn];

int main() {
    int T;
    int n, k;
    ll u, v;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        scanf("%s", s);
        for(int i = 0; i < n; ++i) {
            int f, e;
            if(s[i] == 'L') {
                f = i + 1; e = i;
            } else {
                f = i; e = i + 1;
            }
            p[i] = (f % 2);
        }
        int j = 0;
        for(int i = 0; i <= n; ++i) ans[i] = 1;
        for(int i = 1; i <= n; ++i) {
            if(i == n || p[i] != p[j]) {
                for(int k = j; k <= i; ++k) {
                    if(k % 2 == p[j]) {
                        ans[k] = i - j + 1;
                    }
                }
                j = i;
            }
        }
        for(int i = 0;  i<= n; ++i) printf("%d ", ans[i]);
        printf("\n");
        //printf("%lld\n", ans);
    }
}
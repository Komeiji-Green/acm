#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int maxn = 433333;
char s[maxn];
int main() {
    int T, n;
    cin >> T;
    ll k;
    while(T--) {
        scanf("%d", &n);
        scanf("%s", s + 1);
        for(int i = 1; i <= n; ++i) s[i + n] = s[i];
        int m = 2 * n;
        bool f = 0;
        int sum = 0;
        for(int i = 1, cur = 0; i <= m; ++i) {
            if(i == m || s[i] == 'L') {
                if(i > n) sum += cur / 3;
                cur = 0;
            } else {
                ++cur;
            }
            if(cur >= n) {
                f = 1; break;
            }
        }
        if(f) {
            printf("%d\n", 1 + (n - 1) / 3);
        } else {
            for(int i = 1, cur = 0; i <= m; ++i) {
                if(i == m || s[i] == 'R') {
                    if(i > n) sum += cur / 3;
                    cur = 0;
                } else {
                    ++cur;
                }
                if(cur > n) {
                    f = 1; break;
                }
            }
            printf("%d\n", sum);
        }
        
    }
}
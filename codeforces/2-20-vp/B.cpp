#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

char s[N];
int d[N];
int main() {
    int T, n, k;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &k);
        scanf("%s", s);
        int tot = 0, cnt = 0, ans = 0;
        for(int i = 0, j = -1; i < n; ++i) {
            if(s[i] == 'W') {
                if(i == 0 || s[i-1] == 'L') ans++;
                else ans += 2;
                if(j != -1 && j != i - 1) {
                    d[++tot] = i - j - 1;
                }
                j = i;
                ++cnt;
            }
        }
        int mm = min(n, cnt + k);
        sort(d + 1, d + tot + 1);
        if(cnt == 0) {
            ans = 0;
            if(mm) {
                ans += 2 * mm - 1;
            }
        } else {
            for(int i = 1; i <= tot && cnt < mm; ++i) {
                if(cnt + d[i] <= mm) {
                    ans += 2 * d[i] + 1;
                    cnt += d[i];
                } else {
                    ans += 2 * (mm - cnt); 
                    cnt = mm;
                }
            }
            ans += 2 * (mm - cnt);
        }
        printf("%d\n", ans);

    }
}
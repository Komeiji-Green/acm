
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1000007, inf = 0x3f3f3f3f;
int a[N], dp1[N], dp2[N];
int le[N], ri[N], tp[N], minv[N], ans[N], su[N][3];
void chk(int &y, int w) {
    if(!w) y = w;
}
ll x[N];
int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= k; ++i) {
        scanf("%d %d %lld", &le[i], &ri[i], &x[i]);
        ans[i] = 1;
    }
    for(int b = 0; b < 60; ++b) {
        for(int i = 1; i <= n; ++i) a[i] = 0;
        for(int i = 1; i <= k; ++i) {
            if((1ll<<b)&x[i]) { // type 1
                tp[i] = 1;
                a[le[i]] += 1; a[ri[i] + 1] -= 1;
            } else {
                tp[i] = 2;
            }
        }
        a[n+1] = 0;
        for(int i = 1; i <= n; ++i) a[i] += a[i-1];

        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= 2; ++j) su[i][j] = su[i-1][j];
            su[i][min(a[i], 2)]++;
        }

        for(int i = 1; i <= k; ++i) {
            for(int j = 0; j <= 2; ++j) {
                if(su[ri[i]][j] - su[le[i]-1][j]) {
                    minv[i] = j; break;
                }
            }
        }

        int cnt = 0, bad = 0;
        int rmin = n, lmax = 1;
        for(int i = 1; i <= k; ++i) {
            if(tp[i] == 2) {
                if(minv[i]) ++cnt;
                if(minv[i] >= 2) bad = 1;
                if(minv[i] == 1) {
                    rmin = min(rmin, ri[i]);
                    lmax = max(lmax, le[i]);
                }
            }
        }
        for(int i = 1; i <= k; ++i) {
            if(tp[i] == 2) {
                if(cnt >= 2) chk(ans[i], 0);
                else if(cnt == 0) chk(ans[i], 1);
                else if(minv[i]) chk(ans[i], 1);
                else chk(ans[i], 0);
            }
        }

        dp1[0] = 0; dp2[n+1] = n+1;
        for(int i = 1; i <= n; ++i) {
            dp1[i] = dp1[i-1];
            if(a[i] == 1) dp1[i] = i;
        }
        for(int i = n; i >= 1; --i) {
            dp2[i] = dp2[i+1];
            if(a[i] == 1) dp2[i] = i;
        }

        int lpos, rpos;
        for(int i = 1; i <= k; ++i) {
            if(tp[i] == 1){
                if(bad) chk(ans[i], 0);
                else if(!cnt) chk(ans[i], 1);
                else {
                    if(minv[i] >= 2) {
                        if(cnt == 0) chk(ans[i], 1);
                        else chk(ans[i], 0);
                    } else { // minv[i] == 1
                        //printf("%d: lpos=%d, rpos=%d\n", i, lpos, rpos);
                        lpos = dp2[le[i]]; rpos = dp1[ri[i]];
                        if(lpos <= rmin && rpos >= lmax) chk(ans[i], 1);
                        else chk(ans[i], 0);
                    }
                }
            }
        }
       // printf("%d\n", b);
        //printf("L: %d, R: %d\n", lmax, rmin);
        //for(int i = 1; i <= k; ++i) printf("%d ", minv[i] = query(1, le[i], ri[i], 1, n));
        //printf("\n");
    }
    for(int i = 1; i <= k; ++i) {
        printf("%d",ans[i]);
    }
    printf("\n");
}
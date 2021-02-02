#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll d[233333], a[233333];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        int m = 2 * n;
        for(int i = 1; i <= m; ++i) {
            scanf("%lld", &d[i]);
        }
        sort(d + 1, d + m + 1);
        bool f = 1;
        for(int i = 1; i <= n; ++i) {
            if(d[2 * i - 1] != d[2 * i]) {
                f = 0; break;
            }
        }
        if(f) {
            ll t = 2;
            a[1] = 0;
            for(int i = 2; i <= n; ++i) {
                ll del = d[2 * i] - d[2 * (i - 1)];
                if(del > 0 && del % t == 0) {
                    a[i] = a[i-1] + del / t;
                } else {
                    f = 0; break;
                }
                t += 2;
            }
            if(f) {
                ll sum = d[1];
                ll mysum = 0;
                for(int i = 1; i<= n; ++i) mysum += a[i];
                //cout <<"t: " <<  mysum << endl;
                //for(int i= 1;  i<= n; ++i) printf("%lld ", a[i]);
                //printf("\n");
                mysum *= 2;
                if(sum > mysum && (sum - mysum) % m == 0) {
                    f = 1;
                } else {
                    f = 0;
                }
            }
        }
        if(f) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}
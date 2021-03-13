#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2333;
int a[N], d[N], p[N][N];

int chk(int a1, int a2, int d1, int d2) {
    int r1 = 100, r2 = 100, t1 = 0, t2 = 0;
    while(r1 > 0 && r2 > 0) {
        if(t1 == t2) {
            t1 = d1; t2 = d2;
            r2 -= a1; r1 -= a2;
        } else if(t1 < t2) {
            t2 -= t1; t1 = d1;
            r2 -= a1;
        } else {
            t1 -= t2; t2 = d2;
            r1 -= a2;
        }
    }
    if(r1 <= 0 && r2 <= 0) return 1;
    if(r1 <= 0) return 0;
    return 2;
}
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d %d", &a[i], &d[i]);
        for(int i = 1; i <= n; ++i) for(int j = i; j <= n; ++j) {
            p[i][j]=chk(a[i], a[j], d[i], d[j]);
            p[j][i]=2-p[i][j];
        }
        int mx = 0;
        for(int i = 1; i <= n; ++i) {
            int cur = 0;
            for(int j = 1; j <= n; ++j) {
                cur += p[i][j];
               // printf("%d ",p[i][j]);
            }
            //printf("\n");
            mx = max(mx, cur);
        }
        printf("%.10f\n", (double)mx/(2*n));
    }
}
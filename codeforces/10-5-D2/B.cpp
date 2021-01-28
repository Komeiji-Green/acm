#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;

ll a[105][105];

int m, n;

int rr(int i) {
    return m - i + 1;
}
int rc(int i) {
    return n - i + 1;
}

ll b[105], tot = 0;
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%d%d", &m, &n);
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                scanf("%lld", &a[i][j]);
            }
        }

        ll maxv, minv, cnt = 0;
        for(int i = 1; i <= rr(i); ++i) {
            for(int j = 1; j <= rc(j); ++j) {
                b[0] = a[i][j], b[1] = a[rr(i)][j], b[2] = a[i][rc(j)], b[3] = a[rr(i)][rc(j)];
                if(i != rr(i) && j != rc(j)) {
                    sort(b, b + 4);
                    cnt += b[3] + b[2] - b[1] - b[0];
                } else {
                    maxv = max(max(b[0], b[1]), max(b[2], b[3]));
                    minv = min(min(b[0], b[1]), min(b[2], b[3]));
                    cnt += maxv - minv;
                }
                
            }
        }

        printf("%lld\n", cnt);
    } 
}
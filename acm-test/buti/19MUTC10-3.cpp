#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
double w[maxn];
bool cmp(double a, double b) {
    return a > b;
}
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%lf", &w[i]);
        sort(w + 1, w + n + 1, cmp);
        double q = w[1], r = (1 - w[1]);
        double ans = q, qq, rr;
        for(int i = 2; i <= n; ++i) {
            qq = q * (1 - w[i]) + r * w[i];
            rr = r * (1 - w[i]);
            q = qq; r = rr;
            ans = max(ans, q);
        }
        printf("%.12f\n", ans); 
    }
}
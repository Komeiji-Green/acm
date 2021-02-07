#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 333333;
ll a[maxn], b[maxn];
int main() {
    int n, l, r;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    if(n == 1) {
        printf("%d %d\n%d\n", 1, 1, 0);
        printf("%d %d\n%d\n", 1, 1, 0);
        printf("%d %d\n%lld\n", 1, 1, -a[1]);
    } else {
        printf("%d %d\n", 2, n);
        for(int i = 2; i <= n; ++i) {
            b[i] = a[i] * (n - 1); printf("%lld ", b[i]);
            a[i] += b[i];
        }
        printf("\n");
        printf("%d %d\n%lld\n", 1, 1, -a[1]);
        a[1] = 0;
        printf("%d %d\n", 1, n);
        for(int i = 1; i <= n; ++i) {
            b[i] = -a[i]; printf("%lld ", b[i]);
        }
        printf("\n");
    }
    
}
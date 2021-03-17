#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2333333;
int a[N], b[N];
int main() {
    int T, n, k;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &k);
        int len = 2 * n * (1<<k);
        for(int i = 1; i <= len; ++i) scanf("%d", &a[i]);
        int wd = 1, mid =((1+len)>>1);
        for(int wd = 1; wd < (1<<k); wd <<= 1) {
            int p = mid, q = mid + 1;
            int tot = 0;
            while(p >= 1 && q <= len) {
                for(int i = 0; i < wd; ++i, --p) {
                    b[++tot] = a[p];
                }
                for(int i = 0; i < wd; ++i, ++q) {
                    b[++tot] = a[q];
                }
            }
            for(int i = 1; i <= len; ++i) a[i] = b[i];
        }
        for(int i = 1; i < len; ++i) printf("%d ", a[i]);
        printf("%d\n", a[len]);
    }
}
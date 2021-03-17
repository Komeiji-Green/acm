#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
int a[N], cnt[N];
int main() {
    int T, n, k;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &k);
        n = n - (k - 3);
        int p = 1, q = n;
        while(q % 2 == 0) {
            p *= 2; q /= 2;
        }
        int x, y;
        if(q == 1) {
            x = n / 4, y = n / 2;
        } else {
            x = 1ll * p * ((q-1)/2);
            y = p;
        }
        printf("%d %d %d", x, x, y);
        for(int i = 4; i <= k; ++i) printf(" %d", 1);
        printf("\n");
    }
}
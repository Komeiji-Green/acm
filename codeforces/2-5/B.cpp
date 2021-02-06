#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


int h[3030];
int p[100005];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, k; scanf("%d %d", &n, &k);
        for(int i = 1; i <= n; ++i) scanf("%d", &h[i]);
        int m = 100 * n;
        h[n+1] = 0;
        for(int i = 1; i <= m; ++i) {
            int j = 1;
            for(; j <= n; ++j) {
                if(h[j] < h[j+1]) {
                    h[j]++;
                    break;
                }
            }
            if(j > n) p[i] = -1;
            else p[i] = j;
        }
        if(k > m) {
            printf("-1\n");
        } else {
            printf("%d\n", p[k]);
        }
    }
}
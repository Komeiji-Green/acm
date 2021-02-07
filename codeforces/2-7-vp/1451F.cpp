#include<bits/stdc++.h>
using namespace std;

int a[105][105];
int sg[304];
int main() {
    int T, n, m;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
        }
        for(int d = 1; d <= n + m; ++d) {
            sg[d] = 0;
            for(int i = 1, j; i < d; ++i) {
                j = d - i;
                if(i >= 1 && i <= n && j >= 1 && j <= m)
                    sg[d] ^= a[i][d-i];
            }
        }
        bool f = 0;
        for(int d = 1; d <= n + m; ++d) {
            if(sg[d]) {
                f = 1; break;
            }
        }
        if(f) {
            printf("Ashish\n");
        } else {
            printf("Jeel\n");
        }
    }
}
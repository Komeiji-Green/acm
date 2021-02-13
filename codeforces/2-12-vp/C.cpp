#include<bits/stdc++.h>
using namespace std;

int a[105][150];
int main() {
    int T, n, m;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            a[i][j] += ((a[i][j]-(i+j))%2) ? 1 : 0;
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }
}
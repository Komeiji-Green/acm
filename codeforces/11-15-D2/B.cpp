#include<bits/stdc++.h>
using namespace std;

int a[1001][1001];
int main() {
    int T;
    cin >> T;
    int n, m;
    while(T--) {
        scanf("%d%d", &n, &m);
        int cnt = 0;
        int minv = 1005;
        int sum = 0;
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) {
            scanf("%d", &a[i][j]);
            if(abs(a[i][j]) < minv) minv = abs(a[i][j]);
            sum += abs(a[i][j]);
            if(a[i][j] < 0) ++cnt;
        }
        if(cnt % 2 == 0) {
            printf("%d\n", sum);
        } else {
            printf("%d\n", sum - 2 * minv);
        }
    }
}
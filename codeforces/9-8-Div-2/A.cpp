#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int N = 1050;
int a[N], cnt[2][N];
int main() {
    int T;
    cin >> T;
    int n;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        while(1) {
            memset(cnt, 0, sizeof(cnt));
            for(int i = n; i >= 1; i--) {
                cnt[i % 2][i] = a[i] + cnt[i % 2][i + 1];
                cnt[(i % 2) ^ 1][i] = cnt[(i % 2) ^ 1][i + 1];
            }
            int d = cnt[0][1] - cnt[1][1];
            if(d == 0) break;
            for(int i = n; i >= 1; i--) {
                int dd = cnt[0][i] - cnt[1][i];
                if(d > 0 && dd == 1 || d < 0 && dd == -1) {
                    for(int j = i; j < n; j++) a[j] = a[j + 1];
                    n--;
                    break;
                }
            }
        }
        printf("%d\n", n);
        for(int i = 1; i <= n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
}
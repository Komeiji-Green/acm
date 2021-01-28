#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 2050;
int a[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, k;
        scanf("%d %d", &n, &k);
        for(int i = 1; i <= n; ++i ) {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + 1 + n);
        int d = a[1];
        int cnt = 0;
        for(int i = 2; i <= n; ++i) {
            cnt += (k - a[i]) / d;
        }
        printf("%d\n", cnt);
    }
}
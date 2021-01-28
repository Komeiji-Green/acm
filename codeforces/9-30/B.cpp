#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1005;
int a[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, k;
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        n = unique(a, a + n) - a;
        if(k == 1) {
            if(n == 1) printf("1\n");
            else printf("-1\n");
        } else {
            if(n == 1) printf("1\n");
            else {
                int ans = (n-1 - 1)/(k-1) + 1;
                printf("%d\n", ans); 
            }
        }

    }
}
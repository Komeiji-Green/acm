#include<bits/stdc++.h>
using namespace std;

const int maxn = 233333;
int a[maxn];
int main() {
    int n; cin >> n;
    for(int i = 1; i<= n; ++i) scanf("%d", &a[i]);
    int sum = 0;
    for(int i =1; i<= n; ++i) sum ^= a[i];
    if(n % 2) {
        int m = (n-1)/2;
        printf("YES\n");
        printf("%d\n", n - 1);
        for(int i = 2; i <= n; i += 2) {
            printf("%d %d %d\n", 1, i, i + 1);
        }
        for(int i = 2; i <= n; i += 2) {
            printf("%d %d %d\n", 1, i, i + 1);
        }
    } else {
        if(sum) {
            printf("NO\n");
        } else {
            printf("YES\n");
            printf("%d\n", n - 2);
            n--;
            for(int i = 2; i <= n; i += 2) {
                printf("%d %d %d\n", 1, i, i + 1);
            }
            for(int i = 2; i <= n; i += 2) {
                printf("%d %d %d\n", 1, i, i + 1);
            }
        }
    }
}
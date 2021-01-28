#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int maxn = 10005;
int a[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        scanf("%d", &n);

        int sum = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            sum += a[i];
        }

        if(sum % n) { printf("-1\n"); continue; }

        int avr = sum / n;
        printf("%d\n", 3 * (n - 1));
        for(int i = 2; i <= n; ++i) {
            int k = (i - (a[i] % i)) % i;
            printf("%d %d %d\n", 1, i, k);
            a[1] -= k; a[i] += k;
            k = a[i] / i;
            printf("%d %d %d\n", i, 1, k);
            a[1] += a[i]; a[i] = 0;
        }
        for(int i = 2; i <= n; ++i) {
            printf("%d %d %d\n", 1, i, avr);
        }
    }
}


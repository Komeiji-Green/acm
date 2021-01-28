#include<iostream>
#include<cstdio>
using namespace std;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

const int N = 1050;
int a[N];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        int maxv = 0, g = 0, c;
        for(int i = 1; i <= n; i++) {
            maxv = 0;
            for(int j = i; j <= n; j++) {
                if((c = gcd(g, a[j])) > maxv) {
                    maxv = c;
                    swap(a[i], a[j]);
                }
            }
            g = maxv;
        }
        for(int i = 1; i <= n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
}
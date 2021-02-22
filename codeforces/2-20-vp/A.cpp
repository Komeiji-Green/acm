#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

int a[N], b[N];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        int sum = 0;
        for(int i = 1; i <= n; ++i) sum += a[i];
        if(sum == 0) printf("NO\n");
        else {
            if(sum > 0) {
                int j = 0;
                for(int i = 1; i <= n; ++i) {
                    if(a[i] > 0) b[++j] = a[i];
                }
                for(int i = 1; i <= n; ++i) {
                    if(a[i] <= 0) b[++j] = a[i];
                }
                printf("YES\n");
                for(int i = 1; i <= n; ++i) printf("%d ", b[i]);
                printf("\n");
            } else {
                int j = 0;
                for(int i = 1; i <= n; ++i) {
                    if(a[i] < 0) b[++j] = a[i];
                }
                for(int i = 1; i <= n; ++i) {
                    if(a[i] >= 0) b[++j] = a[i];
                }
                printf("YES\n");
                for(int i = 1; i <= n; ++i) printf("%d ", b[i]);
                printf("\n");
            }
        }
    }
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

int a[N], pos[N], b[N];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i= 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            pos[a[i]] = i;
        }
        int top = n, tot = 0;
        for(int i = n; i >= 1; --i) {
            if(pos[i] <= top) {
                for(int j = pos[i]; j <= top; ++j) {
                    b[++tot] = a[j];
                }
                top = pos[i] - 1;
            }
        }
        for(int i = 1; i <= tot; ++i) {
            printf("%d ", b[i]);
        }
        printf("\n");
    }
}
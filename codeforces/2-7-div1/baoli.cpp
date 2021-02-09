#include<bits/stdc++.h>
using namespace std;

int a[40], s[50], t[50];

int calc(int *b, int n) {
    b[0] = 0;
    int num = 0;
    for(int i = 1; i <= n; ++i) {
        if(b[i] != b[num]) {
            b[++num] = b[i];
        }
    }
    return num;
}
int main() {
    int n; cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int m = (1 << n);
    int ns = 0, nt = 0;
    int ans = n;
    for(int i = 0; i < m; ++i) {
        ns = nt = 0;
        for(int j = 0; j < n; ++j) {
            if((1<<j) & i) s[++ns] = a[j+1];
            else t[++nt] = a[j+1];
        }
        ans = min(ans, calc(s, ns) + calc(t, nt));
    }
    printf("%d\n", ans);
}
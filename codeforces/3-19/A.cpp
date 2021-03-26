#include<bits/stdc++.h>
using namespace std;

int main() {
    int T, n, k1, k2, w, b;
    cin >> T;
    while(T--) {
        scanf("%d %d %d %d %d", &n, &k1, &k2, &w, &b);
        int cnt1 = min(k1, k2) + abs(k1-k2) / 2;
        int cnt2 = min(n-k1, n-k2) + abs(k1-k2) / 2;
        if(w <= cnt1 && b <= cnt2) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}
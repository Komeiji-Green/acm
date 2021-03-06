#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 333333;
const int inf = 0x3f3f3f3f;

int a[maxn];
int main() {
    int T, n, u, v;
    cin >> T;
    while(T--) {
        scanf("%d %d %d", &n, &u, &v);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);

        int minv = a[1], maxv = a[1];
        for(int i = 2; i <= n; ++i) minv = min(minv, a[i]), maxv = max(maxv, a[i]);
        bool f = 0;
        for(int i = 1; i < n; ++i) {
            if(abs(a[i] - a[i+1]) > 1) f = 1;
        }
        int ans;
        if(f) {
            ans = 0;
        } else if(minv == maxv) {
            ans = min(u + v, v + v);
        } else {
            ans = min(u, v);
        }
        printf("%d\n", ans);
    }
}
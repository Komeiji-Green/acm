#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 333333;
int b[maxn];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &b[i]);
        }
        bool f = 0;
        set<int> mp;
        for(int i = 1; i <= n; ++i) {
            if(mp.count(b[i])) {
                f = 1; break;
            }
            mp.insert(b[i]);
        }
        if(f) printf("YES\n");
        else printf("NO\n");
    }
}
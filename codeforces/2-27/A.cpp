#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        bool f = 1;
        for(int i = 1; i < n; ++i) {
            if(a[i] != a[i + 1]) f = 0;
        }
        if(f) {
            printf("%d\n", n);
        } else {
            printf("%d\n", 1);
        }
        
    }
}
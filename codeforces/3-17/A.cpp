#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2333333;
int a[N], vis[N], b[N];
int main() {
    int T, n, k;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for(int i = 1; i <= n; ++i) vis[i] = 0;
        int cnt = 0;
        for(int i = 0; i <= 100; ++i) {
            bool f = 0;
            for(int j = 1; j <= n; ++j) {
                if(a[j] == i) {
                    vis[j] = 1;
                    b[i+1] = a[j];
                    f = 1;
                    break;
                }
            }
            if(!f) break;
            else cnt = i + 1;
        }
        for(int i = 1; i <= n; ++i) {
            if(!vis[i]) b[++cnt] = a[i];
        }
        for(int i = 1; i <= n; ++i) printf("%d ", b[i]);
        printf("\n");
    

    }
}
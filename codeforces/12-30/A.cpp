#include<bits/stdc++.h>
using namespace std;

int x[1055];
bool vis[105];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &x[i]);
        }
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; ++i) {
            for(int j = i + 1; j <= n; ++j) {
                vis[x[j]-x[i]] = 1;
            }
        }
        int cnt=  0;
        for(int i = 1; i <= 100; ++i) {
            if(vis[i]) ++cnt;
        }
        printf("%d\n", cnt);
    }
}
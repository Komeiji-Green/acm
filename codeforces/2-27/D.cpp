#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 433333;
char s[maxn];
bool vis[maxn];
int len[maxn], tot;
int main() {
    int T, n;
    cin >> T;
    ll k;
    while(T--) {
        scanf("%d", &n);
        scanf("%s", s);
        int m = 2 * n;
        bool f = 1;
        int sum = 0;

        for(int i = 0; i + 1 < n; ++i) {
            if(s[i] != s[i + 1]) f = 0;
        }
        if(f) printf("%d\n", 1 + (n - 1) / 3);
        else {
            tot = 0; for(int i = 0; i < n; ++i) vis[i] = 0;

            for(int i = 0; i < n; ++i) {
                if(vis[i]) continue;
                if(s[(i+n-1)%n] == 'R') continue;
                int cur = 0;
                for(int j = 0; j < n; ++j) {
                    vis[(i+j)%n] = 1;
                    if(s[(i+j)%n] == 'R') ++cur;
                    else break; 
                }
                len[++tot] = cur;
            }
            for(int i = 1; i <= tot; ++i) {
                if(len[i] == n) {
                    f = 1; break;
                } else {
                    sum += len[i] / 3;
                }
            }
            tot = 0; for(int i = 0; i < n; ++i) vis[i] = 0;
            for(int i = 0; i < n; ++i) {
                if(vis[i]) continue;
                if(s[(i+n-1)%n] == 'L') continue;
                int cur = 0;
                for(int j = 0; j < n; ++j) {
                    vis[(i+j)%n] = 1;
                    if(s[(i+j)%n] == 'L') ++cur;
                    else break; 
                }
                len[++tot] = cur;
            }
            for(int i = 1; i <= tot; ++i) {
                sum += len[i] / 3;
            }
            printf("%d\n", sum);
        }
        
    }
}
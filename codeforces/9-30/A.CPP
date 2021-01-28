#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;


const int maxn = 1005;
int a[maxn][4];
bool dp[maxn][4];
int fa[maxn][4];
int stk[maxn], tot = 0;
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int k = 0; k < 3; ++k) {
            for(int i = 0; i < n; ++i) {
                scanf("%d", &a[i][k]);
            }
        }
        for(int k = 0; k < 3; ++k) {
            a[n][k] = a[0][k];
        }
        bool flag = false;
        for(int kk = 0; kk < 3 && !flag; ++kk) {
            memset(dp, 0, sizeof(dp));
            memset(fa, 0, sizeof(fa));
            dp[0][kk] = true;
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < 3;++j) {
                    if(!dp[i][j]) continue;
                    for(int k = 0; k < 3; ++k) {
                        if(a[i][j] != a[i+1][k]) {
                            dp[i+1][k] = true;
                            fa[i+1][k] = j;
                        }
                    }
                }
            }
            if(dp[n][kk]) {
                tot = 0;
                for(int i = n, j = kk; i > 0; i--) {
                    j = fa[i][j];
                    stk[tot++] = a[i - 1][j];
                }
                while(tot) {
                    if(tot > 1) printf("%d ", stk[tot - 1]);
                    else printf("%d\n", stk[tot - 1]);
                    tot--;
                }
                break;
            }
        }
    }
}

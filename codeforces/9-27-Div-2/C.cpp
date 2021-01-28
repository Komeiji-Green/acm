#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;


const int maxn = 1000050;
int a[maxn], nxt[maxn], p[maxn];
int stk[maxn], top = 0;
int ans[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        for(int i = 1; i <= n; ++i) {
            p[i] = n + 1;
        }
        for(int i = n; i >= 1; --i) {
            nxt[i] = p[a[i]];
            p[a[i]] = i;
        }

        for(int i = 1; i <= n; ++i) {
            ans[i] = -1;
        }

        top = 0;
        stk[top++] = n + 1;
        for(int i = 1; i <= n; ++i) {
            int maxv = p[i];
            for(int j = p[i]; j <= n; j = nxt[j]) {
                maxv = max(maxv, nxt[j] - j);
            }
            if(maxv < stk[top - 1]) {
                for(int j = maxv; j < stk[top - 1]; ++j) {
                    ans[j] = i;
                }
                stk[top++] = maxv;
            }
        }
        for(int i = 1; i <= n; i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
}
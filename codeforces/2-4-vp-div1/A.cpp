#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
const int maxn = 233333;
int x[maxn], y[maxn], nxt[maxn], vis[maxn];
bool inq[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) nxt[i] = 0, vis[i] = 0, inq[i] = 0;
        for(int i = 1; i <= m; ++i) {
            scanf("%d %d", &x[i], &y[i]);
            nxt[x[i]] = y[i]; vis[y[i]] = 1;
        }
        int cnt = 0;
        for(int x = 1; x <= n; ++x) {
            if(!vis[x] && nxt[x]) {
                for(int i = nxt[x]; i; i = nxt[i]) {
                    ++cnt; inq[i] = 1;
                }
            }
        }
        for(int x = 1; x <= n; ++x) {
            if(nxt[x] && vis[x] && !inq[x]) {
                int len = 1;
                inq[x] = 1;
                for(int i = nxt[x]; i != x; i = nxt[i]) {
                    ++len;
                    inq[i] = 1;
                }
                if(len > 1) cnt += len + 1;
            }
        }
        printf("%d\n", cnt);
    }
}
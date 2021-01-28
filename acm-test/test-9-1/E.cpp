#include<iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;

int f[15];
int sg[1050];
int DP(int n, int m)
{
    sg[0] = 0;
    bool vis[1050];
    for(int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        for(int a = 0, b; (b = (i - a - m)) >= a; a++) {
            vis[sg[a] ^ sg[b]] = true;
        }
        for(int j = 0; j <= 1000; j++) {
            if(!vis[j]) {
                sg[i] = j;
                break;
            }
        }
    }
    int ret = 0;
    if(n >= m) {
        for(int j = 0; j <= 1000; j++) {
            if(j != sg[n - m]) {
                ret = j;
                break;
            }
        }
    }
    return ret;
}

int main()
{
    int T;
    cin >> T;
    int n, m;
    for(int cas = 1; cas <= T; cas++) {
        scanf("%d %d", &n, &m);
        int ans = DP(n, m);

        printf("Case #%d: ", cas);
        if(ans) {
            printf("aekdycoin\n");
        } else {
            printf("abcdxyzk\n");
        }
    }
}
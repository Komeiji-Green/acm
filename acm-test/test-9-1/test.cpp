#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int s[150], sg[10050], n;
int getSG(int x)
{
    if (sg[x] != -1) return sg[x];
    bool vis[150];
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        if (s[i] <= x) {
            getSG(x - s[i]);
            vis[sg[x - s[i]]] = true;
        }
    }
    int pos;
    for (int i = 0;; i++)
        if (!vis[i]) {
            pos = i;
            break;
        }
    return sg[x] = pos;
}
int main()
{
    int cas, t, hps, hei;
    while (scanf("%d", &n) && n != 0) {
        for (int i = 0; i < n; i++)
            scanf("%d", &s[i]);
        memset(sg, -1, sizeof(sg));
        sort(s, s + n);

        scanf("%d", &cas);
        while(cas--) {
            scanf("%d", &hps);
            int ans = 0;
            while (hps--) {
                scanf("%d", &hei);
                ans ^= getSG(hei);
            }
            printf(ans == 0 ? "L" : "W");
        }
        printf("\n");
    }
}
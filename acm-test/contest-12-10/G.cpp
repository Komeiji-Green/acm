#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


ll dp[(1<<18)]; int dpp[1<<18];
int G[20][20], bit[50], p[50], rb[1<<18];
int tag[20];
int n, m;

int a[(1<<18)], deg[1<<18];

void print(int x) {
    for(int i = 4; i >= 0; --i) {
        printf("%d", ((1<<i)&x) ? 1 : 0);
    }
}

int main() {
    cin >> n >> m;
    int u, v;
    for(int i = 1; i <= m; ++i) { 
        scanf("%d %d", &u, &v); --u; --v;
        G[u][v] = G[v][u] = 1;
    }

    for(int i = 0; i < 30; ++i) bit[i] = (1<<i);
    for(int i = 0; i < 18; ++i) rb[1<<i] = i;
    int tot = (1<<n);
    for(int i = 0; i < tot; ++i) {
        for(int j = 0; j < n; ++j) if(i&bit[j]) ++deg[i];
    }
    queue<int> q; q.push(0);
    int id = 0;
    while(!q.empty()) {
        int x = q.front(), y; q.pop();
        a[id++] = x;
        for(int i = 0; i < n; ++i) {
            if(!(x&bit[i])) {
                y = (x | bit[i]);
                if(!(--deg[y])) q.push(y);
            }
        }
    }

    bool flag, st; dp[0] = 1;
    for(int i = 0, x, y, cnt, cur, nex; i < tot; ++i) {
        x = a[i]; cnt = 0; if(!dp[x]) continue;
        //printf("%d %lld\n", x, dp[x]);
        for(int j = 0; j < n; ++j) {
            if(!(bit[j]&x)) p[cnt++] = j;
        }
        dpp[0] = 0;
        for(int j = 1, prev, low; j < bit[cnt]; ++j) {
            prev = (j - (j & (-j)));
            low = rb[j & (-j)];
            dpp[j] = -1;
            if(dpp[prev] == -1 || (bit[low]&dpp[prev])) continue;   // 不具有独立性
            dpp[j] = (dpp[prev] | bit[low]);
            for(int k = 0; k < cnt; ++k) {
                if(G[p[low]][p[k]]) dpp[j] |= bit[k];
            }
            if(dpp[j] == (bit[cnt]-1))  {   // 最大独立集
                y = x;
                for(int k = 0; k < cnt; ++k) {
                    if(bit[k]&j) y |= bit[p[k]];
                }
                dp[y] += dp[x];
                //print(x); cout << " -> "; print(y);
                //cout << endl;
            }
        }
        //for(int j = 0; j < bit[cnt]; ++j) { print(dpp[j]); printf(" "); }
        //cout << endl;
    }
    ll ans = dp[(1<<n)-1];
    printf("%lld\n", ans); 
}
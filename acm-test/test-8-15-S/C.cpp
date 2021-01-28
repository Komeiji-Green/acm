#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 305;
const int INF = 0x3f3f3f3f;

#define rep(i, a, b) for(int i = a; i <= b; i++)

const int N = 300;
int lx[N], ly[N], slack[N], visx[N], visy[N], linker[N];
int G[N][N];
int n, nx, ny;

bool dfs(int x) {
    visx[x] = true;
    int tempDelta;
    rep(y, 1, ny) {
        if(visy[y]) continue;
        tempDelta = lx[x] + ly[y] - G[x][y];
        if(tempDelta == 0) {
            visy[y] = true;  
            if(!linker[y] || dfs(linker[y])) {
                linker[y] = x;
                return true;
            }
        } else if(slack[y] > tempDelta)
                slack[y] = tempDelta;
    }
    return false;
}

void KM() {
    rep(x, 1, nx) {
        rep(j, 1, ny) slack[j] = INF;
        while(true) {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if(dfs(x)) break;
            else {
                int delta = INF;
                rep(j, 1, ny) 
                    if(!visy[j] && slack[j] < delta) 
                        delta = slack[j];
                rep(i, 1, nx)
                    if(visx[i]) 
                        lx[i] -= delta;
                rep(j, 1, ny)
                    if(visy[j])
                        ly[j] += delta;
                    else 
                        slack[j] -= delta;
            }
        }
    }
}

void init() {
    memset(linker, 0, sizeof(linker));
    memset(ly, 0, sizeof(ly));
    rep(i, 1, nx) {
        int temp = 0;
        rep(j, 1, ny) {
            if(G[i][j] > temp) temp = G[i][j];
        }
        lx[i] = temp;
    }
}

int main()
{
    int T;
    cin >> T;
    while(T--) {

        memset(G, 0, sizeof(G));

        int m;
        cin >> n >> m;
        nx = ny = n;
        int u, v, w;
        rep(i, 1, m) {
            scanf("%d %d %d", &u, &v, &w);
            G[u][v] = max(G[u][v], 10001 - w);
        }

        init();
        KM();

        int ans = 0;
        rep(i, 1, ny) {
            int x = linker[i];
            ans += 10001 - G[x][i];
        }
        printf("%d\n", ans);
    }
}
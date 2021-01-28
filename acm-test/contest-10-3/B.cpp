/*
需要在O(1)的时间找到任意一条边，使用邻接矩阵存储更为方便
*/
#include <cstring>
#include <cstdio>
typedef long long ll;
const int maxn = 305;
const int INF = 0x3f3f3f3f;

#define rep(i, a, b) for(int i = a; i <= b; i++)

const int N = 305;
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
    while(scanf("%d", &n) != EOF) {
        nx = n, ny = n;
        rep(i, 1, n) rep(j, 1, n) {
            scanf("%d", &G[i][j]);
        }
        init();
        KM();
        ll ans = 0;
        rep(j, 1, ny) {
            if(linker[j])
                ans += G[linker[j]][j];
        }
        printf("%lld\n", ans);
    }
}

int main() {
    
}
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const ll INF = 0x7fffffff;
#define P pair<int, ll>
#define mp make_pair

#define rep(i, a, b) for(int i = a; i <= b; i++)

const int N = 2005;
ll lx[N], ly[N], slack[N], visx[N], visy[N], linker[N];
ll G[N][N];
int nx, ny;

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

ll edge[N][N];
ll dis[N][N]; 

// 支持有向图、需要读入时处理重边
void floyd(int n)
{
    rep(i, 1, n) rep(j, 1, n) {
        dis[i][j] = edge[i][j];
    }

    //ll minCircle = INF;
    rep(k, 1, n) {
        /*rep(i, 1, k - 1)
            rep(j, i, k - 1) {
                if(G[i][k] == 0 || G[k][j] == 0) continue;
                minCircle = min(minCircle, G[i][k] + G[k][j] + dis[i][j]);
            }*/
        rep(i, 1, n)
            rep(j, 1, n) {
                //if(i == j || i == k || k == j) continue;
                //if(dis[i][j] == -1) dis[i][j] = dis[i][k] + dis[k][j];
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
    }
}

vector<P> port[N];
int vessel[N];
int main()
{
    int n, m, k, p;
    while(scanf("%d", &n) != EOF) {
        scanf("%d %d %d", &m, &k, &p);
        rep(i, 1, n) {
            scanf("%lld", &vessel[i]);
        }

        rep(i, 1, n + m) rep(j, 1, n + m) {
            if(i == j) edge[i][j] = 0;
            else edge[i][j] = INF;
        }

        int a, b;
        ll c;
        rep(i, 1, k) {
            scanf("%d %d %lld", &a, &b, &c);
            edge[a][b] = min(edge[a][b], c);
            edge[b][a] = edge[a][b];
        }

        rep(i, 1, p) {
            scanf("%d %d %lld", &a, &b, &c);
            edge[m + a][b] = min(edge[m + a][b], c);
        }

        floyd(m + n);

        rep(i, 1, n) rep(j, 1, n) {
            G[i][j] = -INF;
        }

        rep(i, 1, n) rep(j, 1, n) {
            G[i][j] = -dis[m + i][vessel[j]];
        }

        nx = ny = n;
        init();
        KM();
        
        ll ans = 0;
        rep(j, 1, ny) {
            ans += -G[linker[j]][j];
        }

        printf("%lld\n", ans);
    }
}
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
#define P pair<int, int>
#define mp make_pair

#define rep(i, a, b) for(int i = a; i <= b; i++)

const int N = 2005;
int lx[N], ly[N], slack[N], visx[N], visy[N], linker[N];
int G[N][N];
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

int edge[N][N];
int dis[N][N]; 

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
                if(i == j || i == k || k == j) continue;
                if(dis[i][j] == -1) dis[i][j] = dis[i][k] + dis[k][j];
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
            scanf("%d", &vessel[i]);
        }

        rep(i, 1, m) rep(j, 1, m) {
            if(i == j) edge[i][j] = 0;
            else edge[i][j] = INF;
        }

        int a, b, c;
        rep(i, 1, k) {
            scanf("%d %d %d", &a, &b, &c);
            edge[a][b] = min(edge[a][b], c);
        }

        floyd(m);

        rep(i, 1, p) {
            scanf("%d %d %d", &a, &b, &c);
            port[a].push_back(mp(b, c));
        }

        rep(i, 1, n) rep(j, 1, n) {
            G[i][j] = -INF;
        }
        rep(i, 1, n) {
            for(auto pr : port[i]) {
                int mid = pr.first;
                int d = pr.second;
                rep(j, 1, n) {
                    int y = vessel[j];
                    G[i][j] = max(G[i][j], -(d + dis[mid][y]));
                }
            }
        }

        nx = ny = n;
        init();
        KM();
        
        int ans = 0;
        rep(j, 1, ny) {
            ans += -G[linker[j]][j];
        }

        printf("%d\n", ans);
    }
}
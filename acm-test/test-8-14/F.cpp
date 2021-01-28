/*
需要在O(1)的时间找到任意一条边，使用邻接矩阵存储更为方便
*/
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;
typedef long long ll;
const int maxn = 305;
const int INF = 0x3f3f3f3f;

#define rep(i, a, b) for(int i = a; i <= b; i++)

const int N = 30;
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

char s[10050];
char t[10050];
char tmp[4];

int main()
{
    int T;
    cin >> T;
    int num, k, m;
    while(T--) {
        scanf("%d %d %d", &num, &k, &m);
        nx = 26, ny = 26;

        rep(i, 1, num) {
            scanf("%s", tmp);
            s[i] = tmp[0];
        }

        rep(i, 1, m) {
            memset(G, 0, sizeof(G));
            rep(j, 1, num) {
                scanf("%s", tmp);
                t[j] = tmp[0];
                G[t[j] - 'A' + 1][s[j] - 'A' + 1]++;
                //G[s[j] - 'A'][t[j] - 'A']++;
            }
            init();
            KM();
            int ans = 0;
            rep(j, 1, ny) {
                if(linker[j])
                    ans += G[linker[j]][j];
            }
            printf("%0.4f\n", (double)(ans) / num);
            //cout << fixed << setprecision(4) << (double)(ans) / num << endl;
        }
    }
}
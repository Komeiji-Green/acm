#include<iostream>
#include<cstring>
#include<set>
#include <vector>
#include <algorithm>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

const int maxn = 10;
const int INF = 0x3f3f3f3f;

int m, n;


int f[maxn];
int find(int x)
{
    if (f[x] == x)
        return x;
    return f[x] = find(f[x]);
}

void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    f[fx] = fy;
}


void init()
{
    for(int i = 1; i <= n; i++) {
        f[i] = i;
    }
}

// 并查集判连通性

vector<int> G[maxn][maxn];
int deg[maxn];

int maxv[maxn];
int cnc[maxn];
vector<int> cnclist[maxn];
int cncnum = 0;

int main()
{
    cin >> m;
    n = 4;
    int u, v, w;
    init();
    rep(i, 1, m) {
        scanf("%d %d %d", &u, &w, &v);
        G[u][v].push_back(w);
        if(u != v)
            G[v][u].push_back(w);
        merge(u, v);
    }

    rep(i, 1, 4) {
        rep(j, 1, 4) {
            if(i != j)
                deg[i] += G[i][j].size();
            else
                deg[i] += (G[i][j].size() * 2);
        }
    }

    rep(i, 1, 4) {
        if(f[i] == i) {
            cncnum++;
            cnc[i] = cncnum;
        }
    }

    rep(i, 1, 4) {
        cnclist[cnc[find(i)]].push_back(i);
    }

    int ans = 0;

    rep(id, 1, 4) {
        int cnt = 0;
        vector<int> &li = cnclist[id];
        for(int i = 0; i < li.size(); i++) {
            if(deg[li[i]] % 2)  cnt++;
        }
        int sum = 0;
        for(int i = 0; i < li.size(); i++) {
            for(int j = i; j < li.size(); j++) {
                for(auto e : G[li[i]][li[j]]) {
                    sum += e;
                }
            }
        }

        int minv = INF;

        if(cnt == 2 || cnt == 0) {
            ans = max(ans, sum);
        } else if(cnt == 4) {
            int minv = INF;
            for(int i = 0; i < li.size(); i++) {
                for(int j = i + 1; j < li.size(); j++) {
                    for(auto e : G[li[i]][li[j]])
                        minv = min(minv, e);
                }
            }

            if(minv != INF)
                sum -= minv;
            ans = max(ans, sum);
        }
    }

    printf("%d\n", ans);
}
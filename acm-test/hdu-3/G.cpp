#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1000000;

const int N = 55;
int G[N][N], dis[N], p[N], vis[N];

int n;

void dij() {
    p[1] = 0;
    for(int i = 2; i <= n; ++i) dis[i] = G[1][i], p[i] = 1, vis[i] = 0;
    for(int i = 2; i <= n; ++i) {
        int k = 0, minv = INF;
        for(int j = 2; j <= n; ++j) {
            if(!vis[j] && dis[j] <= minv) {
                k = j; minv = dis[j];
            }
        }
        vis[k] = 1;
        for(int j = 2; j <= n; ++j) {
            if(!vis[j] && dis[j] > dis[k] + G[k][j]) {
                p[j] = k;
                dis[j] = dis[k] + G[k][j];
            }
        }
    }
}

int gao(int k) {
    dij();
    int res = dis[n];
    if(!k) return res;
    vector<int> vec;
    for(int x = n; x; x = p[x]) {
        vec.push_back(x);
    }
    int sz = vec.size(), len;
    for(int i = 0; i + 1 < sz; ++i) {
        len = G[vec[i]][vec[i+1]];
        G[vec[i]][vec[i+1]] = G[vec[i+1]][vec[i]] = INF;
        res = max(res, gao(k-1));
        G[vec[i]][vec[i+1]] = G[vec[i+1]][vec[i]] = len;
    }
    return res;
}

int main() {
    int T, k, m;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &k);
        m = n * (n - 1) / 2;
        for(int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            G[u][v] = G[v][u] = w;
        }
        int res = gao(k);
        printf("%d\n", res);
    }
}
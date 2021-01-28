#include<iostream>
#include<cstring>
#include<set>
using namespace std;

const int maxn = 10000;

int m, n;
int D[maxn];


int f[maxn];
int w[maxn];    // 边数
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
    w[fx] += w[fy];
    f[fx] = fy;
}

void add(int x, int val) {
    int fx = find(x);
    w[fx] += val;
}

void init()
{
    memset(D, 0, sizeof(D));
    memset(w, 0, sizeof(w));
    for(int i = 1; i <= n; i++) {
        f[i] = i;
    }
}

// 并查集判连通性
set<int> sonGraph;
bool connect() {
    sonGraph.clear();
    for(int i = 1; i <= n; i++) {
        sonGraph.insert(find(i));
    }
    int cnt = 0;
    for(auto it = sonGraph.begin(); it != sonGraph.end(); it++) {
        if(w[*it] > 0) cnt++;
    }
    return cnt <= 1;
}

int main()
{
    int u, v;
    // 是连通图且均为偶度
    while(scanf("%d", &n) != EOF && n != 0) {
        scanf("%d", &m);
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d %d", &u, &v);
            D[u]++; D[v]++;
            merge(u, v);
            add(u, 1);  // 总边数+1
        }

        bool ok = connect();

        for(int i = 1; i <= n; i++) {
            if(D[i] % 2) { 
                ok = false;
                break;
            }
        }
        cout << ok << endl;
    }
}
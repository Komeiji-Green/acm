#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1005;
const int inf = 0x3f3f3f3f;

int a[N][N];

struct Edge {
    int u, v, w;
    bool operator<(const Edge& b) {
        return w < b.w;
    }
};

int fa[N], wei[N], num;

void dfs(int *li, int n, int dad) {
    //if(n != 0) printf("%d\n", n);
    if(n == 1) {
        fa[li[1]] = dad;
        wei[li[1]] = a[li[1]][li[1]];
        return;
    }
    int x, y, maxv = 0;
    for(int i = 1; i <= n; ++i) {
        x = li[i];
        for(int j = i + 1; j <= n; ++j) {
            y = li[j];
            maxv = max(maxv, a[x][y]);
        }
    }
    int id[N]; for(int i = 1; i <= n; ++i) id[i] = 0;
    int tot = 0;
    for(int i = 1; i <= n; ++i) {
        x = li[i];
        if(id[i] < tot) continue;
        bool f = 0;
        for(int j = 1; j <= n; ++j) {
            if(i == j) continue;
            y = li[j];
            if(a[x][y] == maxv) {
                if(id[j] == tot) {id[j]++; f = 1;}
            }
        }
        ++tot;
    }
    int rt = ++num;
    wei[rt] = maxv;
    fa[rt] = dad;

    int vec[N], cnt = 0;
    for(int i = 0; i < tot; ++i) {
        cnt = 0;
        for(int j = 1; j <= n; ++j) {
            if(id[j] == i) {
                vec[++cnt] = li[j];
            }
        }
        dfs(vec, cnt, rt);
    }
}
int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) {
        scanf("%d", &a[i][j]);
    }
    num = n;
    int li[N] = {};
    for(int i = 1; i <= n; ++i) li[i] = i;
    dfs(li, n, 0);
    printf("%d\n", num);
    for(int i = 1; i <= num; ++i) printf("%d ", wei[i]);
    printf("\n");

    int r = n + 1;
    printf("%d\n", r);
    for(int i = 1; i <= num; ++i) {
        if(i == r) continue;
        printf("%d %d\n", i, fa[i]);
    }
}

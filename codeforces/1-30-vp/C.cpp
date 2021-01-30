#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int fa[55];
vector<int> vec[35];
int bit[1<<21], g[1<<21];
int hbit(int x) {
    int i;
    for(i = 21; i >= 0; --i) {
        if((1<<i)&x) return i;
    }
    return i;
}
int ans[1<<22], tot;
void dfs(int x, int op) {
    int sz = vec[x].size();
    int m = (1<<sz);
    if(op) ans[++tot] = x;
    if(op) {
        for(int i = 1, j, b; i < m; ++i) {
            j = bit[g[i]^g[i-1]]; b = ((g[i] >> j) & 1);
            dfs(vec[x][j], b);
        }
    } else {
        for(int i = m - 2, j, b; i >= 0; --i) {
            j = bit[g[i]^g[i+1]]; b = ((g[i] >> j) & 1);
            dfs(vec[x][j], b);
        }
    }
    if(!op) ans[++tot] = x;
}
int main() {
    int n; cin >> n;
    for(int i = 2; i <= n; ++i) scanf("%d", &fa[i]);
    for(int i = 1; i <= n; ++i) vec[fa[i]].push_back(i);
    for(int i = 0; i < 20; ++i) bit[1<<i] = i;
    for(int i = 1; i < (1<<20); ++i) {
        int j = hbit(i);
        g[i] |= (1<<j);
        for(--j; j >= 0; --j) {
            g[i] |= (((i>>1)^i)&(1<<j));
        }
    }
    dfs(0, 1);
    cout << tot - 1 << endl;
    for(int i = 3; i <= tot; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    
}
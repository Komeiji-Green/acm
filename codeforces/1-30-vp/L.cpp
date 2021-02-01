#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int inf = 0x3f3f3f3f;
const int maxn = 233333;
int lch[maxn], rch[maxn], k[maxn], minv[maxn], maxv[maxn], n;

void dfs1(int x) {
    if(x == 0) return;
    minv[x] = maxv[x] = k[x];
    dfs1(lch[x]); if(lch[x]) minv[x] = minv[lch[x]]; 
    dfs1(rch[x]); if(rch[x]) maxv[x] = maxv[rch[x]];
}

int val[maxn], id[maxn], tot;

void dfs2(int x, int L, int R) {
    if(!x) return;
    if(L >= R) return;
    int midl = max(L, maxv[lch[x]]);
    int midr = min(R, minv[rch[x]]);
    dfs2(lch[x], L, midl);
    val[++tot] = midl;
    id[tot] = x;
    dfs2(rch[x], midr, R);
}

int dep[maxn], anc[maxn][30], lg;

// dad是用来防止重复遍历的
void change(int x, int dept) {
    dep[x] = dept;
    for(int i = 1; i <= lg; ++i) {
        if(dep[x] < (1 << i)) break;
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
        //minv[x][i] = min(minv[x][i - 1], minv[anc[x][i - 1]][i - 1]);
    }
    if(lch[x]) {
        int y = lch[x];
        anc[y][0] = x;
        change(y, dept + 1);
    }
    if(rch[x]) {
        int y = rch[x];
        anc[y][0] = x;
        change(y, dept + 1);
    }
}

// 倍增
int lca(int a, int b) {
    if(dep[a] > dep[b]) swap(a, b);
    int d = dep[b] - dep[a];
    for(int i = lg; i >= 0; i--) {
        if(dep[b] < (1 << i)) continue;
        if((1 << i) & d) b = anc[b][i];
    }
    for(int i = lg; i >= 0; i--) {
        if(dep[a] < (1 << i)) continue;
        if(anc[a][i] != anc[b][i]) {
            a = anc[a][i]; b = anc[b][i];
        }
    }
    if(a != b)
        a = anc[a][0], b = anc[b][0];
    return a;
}


int main() {
    int q;
    cin >> n;
    for(lg = 1; lg <= 25; lg++) if((1 << (lg - 1)) > n) break;
    for(int i = 1; i <= n; ++i) {
        scanf("%d %d %d", &lch[i], &rch[i], &k[i]);
    }
    minv[0] = inf; maxv[0] = -inf;
    
    dfs1(1);
    dfs2(1, minv[1], maxv[1]);
    change(1, 1);

    cin >> q;
    int L, R;
    while(q--) {
        scanf("%d%d", &L, &R);
        int vl, vr;
        int ans;
        if((R >= maxv[1] || R < minv[1]) && (L > maxv[1] || L <= minv[1])) {
            ans = 1;
        } else {
            int idx;
            if((R >= maxv[1] || R < minv[1])) vr = 1;
            else { 
                idx = upper_bound(val + 1, val + tot + 1, R) - val;
                --idx;
                vr = id[idx];
            }
            if(L > maxv[1] || L <= minv[1]) vl = 1;
            else {
                idx = lower_bound(val + 1, val + tot + 1, L) - val;
                --idx;
                vl = id[idx];
            }
            int g = lca(vr, vl);
            ans = 2 * (dep[vr] - dep[g]) + 2 * (dep[vl] - dep[g]) + 2 * dep[g] + 1;
        }
        printf("%d\n", ans);
    }
}
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

const int INF = 0x3f3f3f3f;

inline void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

const int M = 233333;
const int N = 233333;

struct Edge {
    int from, to, pre;
    int w;
} e[M];
int last[M];
int tot = 0;

void ine(int a, int b, int w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, int w) {
    ine(a, b, w); ine(b, a, w);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


Edge ee[M];
int la[M];
int es = 0;

void ine3(int a, int b, int w) {
    es++;
    ee[es].from = a; ee[es].to = b; ee[es].w = w;
    ee[es].pre = la[a];
    la[a] = es;
}

inline void ine4(int a, int b, int w) { ine3(a, b, w); ine3(b, a, w); } 

int n;

// 倍增LCA
//int size[N]; // 子树大小
int dep[N]; // 深度
int anc[N][30]; // 祖先
//int minv[N][30]; // 最小权
bool out[N][30];    // 路径有无出边
bool in[N][30];     // 路径有无入边
int lg;

// dad是用来防止重复遍历的
void change(int x, int dad, int dept) {
    //size[x] = 1;
    dep[x] = dept;
    for(lg = 0; lg <= 20; lg++) if(n < (1 << (lg - 1))) break;
    rep(i, 1, lg) {
        if(dep[x] < (1 << i)) break;
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
        in[x][i] = in[x][i - 1] || in[anc[x][i - 1]][i - 1];
        out[x][i] = out[x][i - 1] || out[anc[x][i - 1]][i - 1];
        //minv[x][i] = min(minv[x][i - 1], minv[anc[x][i - 1]][i - 1]);
    }
    for(int i = la[x]; i; i = ee[i].pre) {
        int y = ee[i].to;
        if(y == dad) continue;
        anc[y][0] = x;
        in[y][0] = ee[i].w == 1;
        out[y][0] = !in[y][0];
        //minv[y][0] = ee[i].w;
        change(y, x, dept + 1);
        //size[x] += size[y];
    }
}

bool check(int a, int b) {
    for(lg = 1; lg <= 20; lg++) if((1 << (lg - 1)) > n) break;
    bool flag = false;
    if(dep[a] < dep[b]) { swap(a, b); flag = true; }

    int d = dep[a] - dep[b];
    bool bad = false;
    for(int i = lg; i >= 0; i--) {
        if(dep[a] < (1 << i)) continue;
        if((1 << i) & d) { 
            if(flag == false) {
                bad = bad || in[a][i];
            } else {
                bad = bad || out[a][i];
            }
            a = anc[a][i];
        }
    }

    for(int i = lg; i >= 0; i--) {
        if(dep[a] < (1 << i)) continue;
        if(anc[a][i] != anc[b][i]) {
            bad = bad || (flag ? (out[a][i] || in[b][i]) : (in[a][i] || out[b][i]));
            a = anc[a][i]; b = anc[b][i];
        }
    }
    if(a != b) {
        bad = bad || (flag ? (out[a][0] || in[b][0]) : (in[a][0] || out[b][0]));
        a = anc[a][0]; b = anc[b][0];
    }
    return !bad;
}


int main()
{
    cin >> n;
    int u, v;
    rep(i, 1, n - 1) {
        scanf("%d %d", &u, &v);
        ine3(u, v, 1);
        ine3(v, u, -1);
    }
    change(1, 0, 1);
    int q;
    cin >> q;
    rep(i, 1, q) {
        scanf("%d %d", &u, &v);
        bool ans = check(u, v);
        printf(ans ? "Yes\n" : "No\n");
    }

}
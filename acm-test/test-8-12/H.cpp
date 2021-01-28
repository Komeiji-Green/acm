#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
typedef long long ll;

const int N = 205000;
const int M = 500000;

#define rep(i, a, b) for(int i = a; i <= b; i++)

struct Edge {
    int from, to, pre, w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, int w) {
    tot++;
    e[tot].w = w;
    e[tot].from = a;
    e[tot].to = b;
    e[tot].pre = last[a];
    last[a] = tot;
}

void ine2(int a, int b, int w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int n, m;

int arr[N];
int diff[2][N];  // 差分

int clc = 0;
int p[2];
struct Pos {
    int d;  // 0/1
    int idx;
    int l, r;
    int exl, exr;
} pos[N];   // 记录结点x在树状数组上的下标 

int back[2];

void dfs(int x, int dad, int dept)
{
    //printf("%d\n", clc);
    //clc++;
    //printf("%d\n", x);
    int d = dept % 2;
    p[d]++;
    //pre[d][p[d]] = clc;
    diff[d][p[d]] = arr[x] - back[d];
    back[d] = arr[x];
    pos[x].d = d;
    pos[x].l = pos[x].idx = p[d];
    pos[x].exl = p[d ^ 1] + 1;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        dfs(y, x, dept + 1);
    }
    //post[d][p[d]] = clc;
    pos[x].r = p[d];
    pos[x].exr = p[d ^ 1];
}

int C[2][N];
// 区间编号
void add(int x, int val, int d) {
    for(int i = x; i <= n; i += (i & (-i))) {
        C[d][i] += val;
    }
}
// 区间编号
int query(int x, int d) {
    int ans = 0;
    for(int i = x; i > 0; i -= (i & (-i))) {
        ans += C[d][i];
    }
    return ans;
}

int main()
{
    cin >> n >> m;
    rep(i, 1, n) {
        scanf("%d", &arr[i]);
    }
    int u, v;
    rep(i, 1, n - 1) {
        scanf("%d %d", &u, &v);
        ine2(u, v, 0);
    }

    // 获取dfs序
    dfs(1, 0, 1);

    // 建立树状数组
    rep(d, 0, 1) rep(i, 1, p[d]) {
        add(i, diff[d][i], d);
    }

    /*rep(i, 1, n) {
        printf("%d: %d %d\n", i, pos[i].d, query(pos[i].idx, pos[i].d));
    }*/
    int op, x, val;
    rep(i, 1, m) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %d", &x, &val);
            int d = pos[x].d;
            int l = pos[x].l, r = pos[x].r;
            add(l, val, d); add(r + 1, -val, d);
            l = pos[x].exl, r = pos[x].exr;
            add(l, -val, d ^ 1); add(r + 1, val, d ^ 1);
        } else {
            scanf("%d", &x);
            int d = pos[x].d;
            printf("%d\n", query(pos[x].idx, d));
        }
    }


    /*rep(i, 1, n) {
        printf("%d: %d %d %d %d\n", i, pos[i].l, pos[i].r, pos[i].exl, pos[i].exr);
    }*/
}
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;
typedef long long ll;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)
const int N = 5050;

const int mod = 998244353;

typedef long long ll;

const int M = 10500;

struct Edge {
    int from, to, pre;
    ll w;
};


#define reg(i, x) for(int i = la[x]; i; i = ee[i].pre)

Edge ee[M];
int la[N];
int es = 0;

void ine3(int a, int b, ll w) {
    es++;
    ee[es].from = a; ee[es].to = b; ee[es].w = w;
    ee[es].pre = la[a];
    la[a] = es;
}

inline void ine4(int a, int b, ll w) { ine3(a, b, w); ine3(b, a, w); } 

int n;

int dp_up[N][3];  // 上行距离为k
int dp_down[N][3];  // 下行距离为k
int pos, ppos, pppos;
//int size[N]; // 子树大小
//int dep[N]; // 深度
//int anc[N][30]; // 祖先
//int minv[N][30]; // 最小权

ll ans = 0;
int dis = 0;

// dad是用来防止重复遍历的
void change(int x, int dad) {
    //size[x] = 1;
    if(dad == 0) dp_up[x][pos] = 0;
    int sum = 0;
    reg(i, x) {
        int y = ee[i].to;
        if(y == dad) continue;
        dp_up[y][pos] = dp_up[x][ppos] + dp_down[x][ppos] - dp_down[y][pppos];
        sum += dp_down[y][ppos];
        change(y, x);
    }
    dp_down[x][pos] = sum;
    sum = dp_down[x][pos] + dp_up[x][pos];
    reg(i, x) {
        int y = ee[i].to;
        if(y == dad) ee[i].w = dp_up[dad][ppos] + dp_down[dad][ppos] - dp_down[x][pppos];
        else ee[i].w = dp_down[y][ppos];
    }
    ll temp = 0;
    for(int i = la[x]; i; i = ee[i].pre) {
        for(int j = ee[i].pre; j; j = ee[j].pre) {
            temp += ee[i].w * ee[j].w * (sum - ee[i].w - ee[j].w);
        }
    }
    ans += (temp / 3);
    //printf("%d, %d: %lld\n", dis, x, temp / 3);
}

int main()
{
    cin >> n;
    int u, v;
    rep(i, 1, n - 1) {
        scanf("%d %d", &u, &v);
        ine4(u, v, 0);
    }
    pos = 0; ppos = 2; pppos = 1;
    rep(i, 1, n) {
        dp_down[i][0] = dp_up[i][0] = 1;
        dp_down[i][ppos] = 1;
    }

    ans = 0;
    for(int d = 1; d <= n; d++) {
        dis = d;
        pos = d % 3;
        ppos = (d + 2) % 3;
        pppos = (d + 1) % 3;

        change(1, 0);
        if(dp_down[1][pos] == 0) break;
    }
    printf("%lld\n", ans);
}
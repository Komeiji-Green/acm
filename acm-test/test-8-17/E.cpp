#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 523333;
const int N = 233333;

struct Edge
{
    int from, to, pre;
    ll w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, ll w)
{
    tot++;
    e[tot].from = a;
    e[tot].to = b;
    e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w)
{
    ine(a, b, w);
    ine(b, a, w);
}

#define reg(i, x) for (int i = last[x]; i; i = e[i].pre)

int cnt[N]; // 子树箭头数量
int rt[N];  // 向根节点的路径上的箭头数量
int tag[N]; // 根节点的哪条分支
int head[N];   

void change(int x, int dad, int tg) {
    cnt[x] = 0;
    tag[x] = tg;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        int d = e[i].w == 1;
        rt[y] = rt[x] + (d ^ 1);
        if(dad == 0)
            change(y, x, y);
        else
            change(y, x, tg);
        cnt[x] += cnt[y] + d;
    }
}

void getHead(int x, int dad) {
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        int d = e[i].w;
        head[y] = head[x] + cnt[x] - cnt[y] - d;
        getHead(y, x);
    }
}

int ans[N];
int ansnum = 0;
int main()
{
    int n;
    cin >> n;
    int u, v;
    rep(i, 1, n - 1) {
        scanf("%d %d", &u, &v);
        ine(u, v, 1);
        ine(v, u, -1);
    }
    change(1, 0, 0);
    getHead(1, 0);
    int maxv = 0;
    ansnum = 0;
    rep(i, 1, n) {
        int sum = head[i] + cnt[i];
        //printf("%d %d %d\n", i, head[i], cnt[i]);
        if(sum > maxv) {
            ansnum = 1;
            ans[ansnum] = i;
            maxv = sum;
        } else if(sum == maxv) {
            ansnum++;
            ans[ansnum] = i;
        }
    }
    printf("%d\n", n - 1 - maxv);
    rep(i, 1, ansnum) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}
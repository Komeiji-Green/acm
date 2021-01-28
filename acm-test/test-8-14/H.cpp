#include<iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 2523333;
const int N = 2333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) {
    ine(a, b, w); ine(b, a, w);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int l, r, m;    // 左、右、边

int linker[N];
bool vis[N];
bool dfs(int x) {
    reg(i, x) {
        int y = e[i].to;
        if(vis[y]) continue;
        vis[y] = true;
        if(!linker[y] || dfs(linker[y])) {
            linker[y] = x;
            return true;
        }
    }
    return false;
}

int Hungarian() {
    int ans = 0;
    memset(linker, 0, sizeof(linker));
    rep(i, 1, l) {
        memset(vis, 0, sizeof(vis));
        if(dfs(i))
            ans++;
    }
    return ans;
}

inline int Time(int h, int m) {
    return h * 60 + m;
}

inline int cost(int a, int b, int c, int d) {
    return abs(a - c) + abs(b - d);
}

struct BK {
    int t, last, a, b, c, d;
} bk[1000];

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        scanf("%d", &n);

        tot = 0;
        memset(last, 0, sizeof(last));

        int hour, min, t;
        int a, b, c, d;
        rep(i, 1, n) {
            scanf("%d:%d", &hour, &min);
            bk[i].t = Time(hour, min);
            scanf("%d %d %d %d", &a, &b, &c ,&d);
            bk[i].a = a; bk[i].b = b; bk[i].c = c; bk[i].d = d;
            bk[i].last = cost(a, b, c, d) + bk[i].t; 
            //printf("%d %d\n", bk[i].t, bk[i].last);
            
            /*
            int flag = -1;
            for(int j = i - 1; j >= 1; j--) {
                if(bk[j].last < bk[i].t) {
                    if(flag == -1) {
                        flag = bk[j].t;
                        ine(j, n + i, 0);
                    } else if(bk[j].last >= flag) {
                        ine(j, n + i, 0);
                    }
                }
            }*/
            /*rep(j, 1, i - 1) {
                if(bk[j].last < bk[i].t)
                    ine(j, n + i, 0);
            }*/ 
        }
        rep(i, 1, n) {
            rep(j, i + 1, n) {
                if(bk[i].last + cost(bk[i].c, bk[i].d, bk[j].a, bk[j].b) < bk[j].t)
                    ine(i, n + j, 0);
            }
        }

        l = n;
        int ans = Hungarian();
        printf("%d\n", n - ans);
    }
}
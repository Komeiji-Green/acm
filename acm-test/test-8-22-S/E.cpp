#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;
typedef long long ll;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

const int N = 2000500;
const int M = 3000500;

const int mod = 998244353;

typedef long long ll;


struct Edge {
    int from, to, pre;
};

Edge ee[M];
int la[N];
int es = 0;

#define reg(i, x) for(int i = la[x]; i; i = ee[i].pre)

void ine(int a, int b) {
    es++;
    ee[es].from = a; ee[es].to = b; 
    ee[es].pre = la[a];
    la[a] = es;
}

inline void ine2(int a, int b) { ine(a, b); ine(b, a); } 

int n;
ll m;

ll w[N];

ll val[N];
int cnt = 0;
void change(int x, int dad) {
    reg(i, x) {
        int y = ee[i].to;
        change(y, x);
    }
    int num = 0;
    reg(i, x) {
        int y = ee[i].to;
        val[++num] = w[y];
    }
    sort(val + 1, val + num + 1);
    rep(i, 1, num) {
        if((w[x] + val[i] - 1) <= m) {
            //printf("%d, %d: %lld %lld\n", x, ch[i].id, wei, ch[i].w);
            w[x] += val[i] - 1;
            cnt++;
        }
    }
}

int main()
{
    cin >> n >> m;
    ll wei;
    rep(i, 1, n) {
        scanf("%lld", &w[i]);
    }

    es = 0;
    memset(la, 0, sizeof(la));
    int v;
    ll k;
    rep(i, 1, n) {
        scanf("%lld", &k);
        w[i] += k;
        rep(j, 1, (int)k) {
            scanf("%d", &v);
            ine(i, v + 1);
        }
    }

    change(1, 0);

    printf("%d\n", cnt);
}
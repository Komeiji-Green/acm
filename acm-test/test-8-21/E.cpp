#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 23333;
const int N = 23333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[M];
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


const double eps = 1e-10;
const double inf = 1e20;
const double pi = acos(-1.0);
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	if(x < 0)return -1;
	else return 1;
}
//square of a double
inline double sqr(double x){return x*x;}

int E[N], K[N];
double A[N], B[N], C[N];
int deg[N];

// 倍增LCA
//int size[N]; // 子树大小
//int dep[N]; // 深度

// dad是用来防止重复遍历的
bool change(int x, int dad, int dept) {
    //size[x] = 1;
    //dep[x] = dept;
    
    bool flag = true;   // 叶子节点
    double a = 0, b = 0, c = 0;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        flag = false;
        if(!change(y, x, dept + 1))
            return false;
        /*
        Ai =        (ki+(1-ki-ei)/m*∑Aj)   / (1 - (1-ki-ei)/m*∑Bj);
        Bi =        (1-ki-ei)/m            / (1 - (1-ki-ei)/m*∑Bj);
        Ci = ( (1-ki-ei)+(1-ki-ei)/m*∑Cj ) / (1 - (1-ki-ei)/m*∑Bj);
        */
        a += A[y], b += B[y], c += C[y];
    }
    if(!flag) {
        int m = deg[x];
        double r = (100 - K[x] - E[x]) / 100.0;
        double d = 1 - r / m * b;
        //if(sgn(d) == 0) return false;
        A[x] = (K[x] / 100.0 + r / m * a) / d;
        B[x] = r / m / d;
        C[x] = (r + r / m * c) / d;
        return true;
    } else {
        A[x] = K[x] / 100.0;
        B[x] = (100 - K[x] - E[x]) / 100.0;
        C[x] = (100 - K[x] - E[x]) / 100.0;
        return true;
    }
}

int main()
{
    int T;
    cin >> T;
    for(int tt = 1; tt <= T; tt++) {
        int n;
        cin >> n;

        tot = 0;
        memset(last, 0, sizeof(last));
        memset(deg, 0, sizeof(deg));
        int u, v;
        rep(i, 1, n - 1) {
            scanf("%d %d", &u, &v);
            ine2(u, v, 0);
            deg[u]++;
            deg[v]++;
        }
        rep(i, 1, n) {
            scanf("%d %d", &K[i], &E[i]);
        }
        // 设E[i] = Ai * E[1] + Bi * E[fa[i]] + Ci 

        printf("Case %d: ", tt);
        bool flag = change(1, 0, 1);
        if(!flag || sgn(1 - A[1]) == 0) {
            printf("impossible\n");
        } else {
            double ans = C[1] / (1 - A[1]);
            printf("%.6f\n", ans);
        }

    }
}
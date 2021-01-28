#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const double eps = 1e-8;
const int N = 100005;
ll c[N];
ll pre[N];
ll dp[N];

int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else if(x < 0) return -1;
    else return 1;
}

ll sqr(ll x) { return x * x; }

struct Point {
    int id;
    ll x, y;
    double g;   // 与上一个点的斜率
    bool operator< (const Point& b) {
        return sgn(g - b.g) < 0;
    }
} que[N];   // 单调队列

bool cmp(const Point& a, const Point& b) {
    int d = sgn(a.g - b.g);
    return d < 0;
}

double grad(const Point& a, const Point& b) {
    double dx = b.x - a.x, dy = b.y - a.y;
    return dy / dx;
}
int head = 0, tail = 0;

int main()
{
    int n;
    ll L;
    cin >> n >> L;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &c[i]);
    }
    pre[0] = 0;
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + c[i];
    }


    head = 0; tail = 1;
    que[0].x = que[0].y = que[0].id = 0;
    for(int i = 1; i <= n; i++) { 
        //  先查询，再插入，单调队列维护
        Point tag;
        tag.g = 2 * (i + pre[i] - L - 1);
        int idx = lower_bound(que + head + 1, que + tail, tag) - que;
        int j = que[idx - 1].id;
        dp[i] = dp[j] + sqr(i + pre[i] - j - pre[j] - L - 1);
        //printf("%d %d %lld\n", i, j, dp[i]);

        Point p;
        p.x = i + pre[i]; p.y = dp[i] + p.x * p.x; p.id = i;
        while(head + 1 < tail && que[tail - 1].g > grad(que[tail - 1], p)) tail--;
        p.g = grad(que[tail - 1], p);
        que[tail++] = p;

        /*for(int i = head + 1; i < tail; i++) {
            printf("%d %f\n", que[i].id, que[i].g);
        }*/
    }
    /*for(int i = 1; i <= n; i++) {
        printf("%d %lld\n", i, dp[i]);
    }*/
    printf("%lld\n", dp[n]);
}
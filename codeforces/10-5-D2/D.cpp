#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
const int N = 2333333;
const ll INF = 0x3f3f3f3f3f3f3f3f;

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
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

bool inq[N];
int Q[N], nums[N]; // nums: 入队次数，判负边
ll dis[N];
void spfa(int s, int n) {
    int head = 0, tail = 0;
    memset(nums, 0, sizeof(nums));
    memset(inq, 0, sizeof(inq));
    rep(i, 1, n) dis[i] = INF;
    Q[tail++] = s;
    inq[s] = true;
    dis[s] = 0;
    while(head < tail) {
        int x = Q[head++];
        inq[x] = false;
        reg(i, x) {
            int y = e[i].to;
            if(dis[y] > e[i].w + dis[x]) {
                dis[y] = e[i].w + dis[x];
                if(!inq[y]) {
                    inq[y] = true;
                    Q[tail++] = y;
                    //nums[i]++;
                    //if(nums[i] >= n) return true;   // 如果n次入队，则有负圈
                }
            }
        }
    }
}

struct Point {
    int x, y, id;
    void input(int _id) {
        id = _id;
        scanf("%d %d", &x, &y);
    }
} p[N], tmp[N];

bool cmpx(const Point& a, const Point& b) {
    return a.x < b.x;
}
bool cmpy(const Point& a, const Point& b) {
    return a.y < b.y;
}
int getdis(const Point &a, const Point& b) {
    return min(abs(a.x - b.x), abs(a.y - b.y));
}


int main() {
    int n, m, sx, sy, tx, ty;
    cin >> n >> m >> sx >> sy >> tx >> ty;
    int x, y;
    for(int i = 1; i <= m; ++i) {
        tmp[i].input(i);
    }
    memcpy(p, tmp, sizeof(tmp));
    sort(p + 1, p + m + 1, cmpx);
    for(int i = 1; i < m; ++i) {
        ine2(p[i].id, p[i + 1].id, getdis(p[i], p[i+1]));
    }
    sort(p + 1, p + m + 1, cmpy);
    for(int i = 1; i < m; ++i) {
        ine2(p[i].id, p[i + 1].id, getdis(p[i], p[i+1]));
    }
    Point s, t;
    s.x = sx, s.y = sy; s.id = m + 1;
    t.x = tx, t.y = ty;
    for(int i = 1; i <= m; ++i) {
        ine(s.id, p[i].id, getdis(s, p[i]));
    }
    spfa(m + 1, m + 1);
    ll maxv = dis[m + 1] + abs(sx - tx) + abs(sy - ty);
    for(int i = 1; i <= m; ++i) {
        maxv = min(maxv, dis[i] + abs(tmp[i].x - tx) + abs(tmp[i].y - ty));
    }
    printf("%lld\n", maxv);
}
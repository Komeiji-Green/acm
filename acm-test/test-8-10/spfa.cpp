#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int INF = 0x3f3f3f3f;
const int M = 2333333;
const int N = 2333333;

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

bool inq[N];
int Q[N];
int dis[N];
int nums[N];    // 入队次数，判负边

bool spfa(int n) {
    int head = 0, tail = 1;
    memset(nums, 0, sizeof(nums));
    rep(i, 1, n) {
        inq[i] = true;
        Q[tail++] = i;  // 考虑到非连通性
        nums[i]++;
        dis[i] = 0;     // 判负边用0，求最短路用INF
    }
    while(head <= tail) {
        int x = Q[head++];
        inq[x] = false;
        reg(i, x) {
            int y = e[i].to;
            if(dis[y] > e[i].w + dis[x]) {
                dis[y] = e[i].w + dis[x];
                if(!inq[y]) {
                    inq[y] = true;
                    Q[tail++] = y;
                    nums[i]++;
                    if(nums[i] >= n) return true;   // 如果n次入队，则有负圈
                }
            }
        }
    }
    return false;
}

void init()
{
    tot = 0;
    memset(last, 0, sizeof(last));
}

int main()
{
    int n, m;
    cin >> n >> m;
    int u, v;
    ll w;
    for(int i = 1; i <= m; i++) {
        scanf("%d %d %lld", &u, &v, &w);
        ine2(u, v, w);
    }
    bool ans = spfa(n);
    cout << ans << endl;
    for(int i = 1; i <= n; i++) {
        printf("%d, dis: %d\n", i, dis[i]);
    }
}
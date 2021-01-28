// topo sorting

#include <iostream>
#include <queue>
#include <cstring>
#include <queue>

using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair
#define P pair<int, int>

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int M = 100503;
const int N = 100503;

struct Edge {
    int from, to, pre;
    int w;
} e[M];
int last[N];
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

int order[N];   // 次序
int deg[N];
// 环路检测
bool check(int n, int k) {
    queue<int> q;   // 入度为0的结点

    int cnt = 0;    // 遍历点的数量
    memset(deg, 0, sizeof(deg));
    rep(x, 1, n) {
        reg(i, x) if(e[i].w > k) deg[e[i].to]++;
    }
    rep(i, 1, n) if(deg[i] == 0) q.push(i);
    while(!q.empty()) {
        cnt++;
        int cur = q.front(); q.pop();
        order[cur] = cnt;
        int y;
        reg(i, cur) if(e[i].w > k) {
            y = e[i].to;
            deg[y]--;
            if(deg[y] == 0)
                q.push(y);
        }
    }
    if(cnt == n) return true;
    else return false;
}

int ans[N];     // 安排fdfdfdfdfdffdfdfdffdfdf
int ansnum = 0;

int main()
{
    int n, m;
    cin >> n >> m;
    int u, v, w;
    tot = 0;
    rep(i, 1, m) {
        scanf("%d %d %d", &u, &v, &w);
        ine(u, v, w);
    }

    int le = 0, ri = 1000000000;
    int mid = (le + ri) >> 1;
    while(le < ri) {
        if(check(n, mid)) {
            ri = mid;
        } else {
            le = mid + 1;
        }
        mid = (le + ri) >> 1;
    }
    check(n, mid);  // 二分答案可能从来未出现过true
    rep(i, 1, tot) {
        if(e[i].w <= mid && order[e[i].to] < order[e[i].from])
            ans[++ansnum] = i;
    }
    
    printf("%d %d\n", mid, ansnum);
    rep(i, 1, ansnum) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}

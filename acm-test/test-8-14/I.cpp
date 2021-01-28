#include<iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 200000;
const int N = 1000;

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

int s[200][200];
struct Pos{
    int r, c;
} pos[12333];

int arr[500];
struct swp {
    int c1, c2;
} ans[1000];
int cnt = 0;

int main()
{
    int sz;
    while(scanf("%d", &sz) != EOF) {
        rep(i, 1, sz) rep(j, 1, sz) {
            scanf("%d", &s[i][j]);
        }

        memset(pos, 0, sizeof(pos));

        tot = 0;
        memset(last, 0, sizeof(last));
        rep(i, 1, sz) rep(j, 1, sz) {
            if(s[i][j] == 1)
                ine(i, sz + j, 0);
        }

        l = sz; r = sz;
        int res = Hungarian();
        if(res != sz) {
            printf("-1\n");
            continue;
        }
        rep(j, sz + 1, sz + sz) {   // 所有的列
            arr[linker[j]] = j - sz;
        }

        /*rep(i, 1, sz) printf("%d ", arr[i]);
        cout << endl;*/

        // 选择排序
        cnt = 0;
        rep(i, 1, sz) {
            rep(j, i, sz) {
                if(arr[j] == i && i != j) {
                    swap(arr[i], arr[j]);
                    cnt++;
                    ans[cnt].c1 = i;
                    ans[cnt].c2 = j;
                    break;
                }
            }
        }
        printf("%d\n", cnt);
        rep(i, 1, cnt) {
            printf("R %d %d\n", ans[i].c1, ans[i].c2);
        }
    }
}
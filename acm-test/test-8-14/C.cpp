#include<iostream>
#include <queue>
#include <cstring>
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

char s[10][10];
struct Pos{
    int r, c;
} pos[100];

int main()
{
    int sz;
    while(scanf("%d", &sz) != EOF && sz != 0) {
        rep(i, 1, sz) {
            scanf("%s", s[i] + 1);
        }

        memset(pos, 0, sizeof(pos));
        int row = 0, col = 0;
        rep(i, 1, sz) {
            row++;
            rep(j, 1, sz) {
                if(s[i][j] == '.') {
                    pos[(i - 1) * 4 + j].r = row;
                } else if(s[i][j] == 'X')
                    row++;
            }
        }
        rep(j, 1, sz) {
            col++;
            rep(i, 1, sz) {
                if(s[i][j] == '.') {
                    pos[(i - 1) * 4 + j].c = col;
                } else if(s[i][j] == 'X')
                    col++;
            }
        }

        tot = 0;
        memset(last, 0, sizeof(last));
        rep(i, 1, 16) {
            if(pos[i].r == 0 || pos[i].c == 0) continue;
            ine(pos[i].r, row + pos[i].c, 0);
        }

        l = row; r = col;
        int ans = Hungarian();
        printf("%d\n", ans);
    }
}
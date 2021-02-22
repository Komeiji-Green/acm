#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)

typedef long long ll;

const int M = 100007;
const int N = 100007;

struct Edge {
    int to, pre, w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, ll w) {
    ++tot;
    e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

ll a[N], b[N], ans[101][N];
int c[N];
int dp[60][N][2][3]; // 位、结点、1/0、和的类别
int st;
void dfs(int x) {
    for(int k = 0; k < 3; ++k) dp[st][x][0][k] = 0;
    int cnt = 0;
    auto sum = dp[st][x];
    
    for(int i = last[x], y, w; i; i = e[i].pre) {
        y = e[i].to; w = e[i].w;
        ++cnt;
        for(int j = 0; j < 2; ++j) {
            switch(w) {
                case 0:
            }
        }

    }
}
int main() {
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for(int i = 2, f, s; i <= n; ++i) {
        scanf("%d %d", &f, &s);
        ine(f, i, s); 
    }
    for(int d = 0; d <= 100; ++d) {
        for(int i = 1; i <= n; ++i) {
            b[i] = a[i] + 1ll * i * d;
            for(int j = 0; j < 60; ++j) {
                c[i][j] = ((b[i]>>j)&1);
            }
        }
        for(int j = 0; j < 60; ++j) {
            st = j;
            dfs(1);
        }
    }
}
#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3f;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

struct Mat {
    Mat() {}
    Mat(ll *list, int _m, int _n):
        m(_m), n(_n) 
    {
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                a[i][j] = list[i * n + j];
            }
        }
    }
    Mat operator* (const Mat& rhs) {
        Mat ans;
        int p = rhs.n;
        ans.m = m; ans.n = p;
        ll sum;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < p; j++) {
                sum = -1;
                for(int k = 0; k < n; k++) {
                    if(a[i][k] >= 0 && rhs.a[k][j] >= 0)
                        sum = max(sum, a[i][k] + rhs.a[k][j]);
                }
                ans.a[i][j] = sum;
            }
        }
        return ans;
    }
    int m, n;
    ll a[205][205];
};

// 快速幂 计算 a^k % p
// a <= 1e9, k <= 1e9
Mat Pow(Mat a, ll k) 
{
    Mat ans;
    ans.m = ans.n = a.m;
    for(int i = 0; i < ans.m; i++) {
        for(int j = 0; j < ans.n; j++) {
            if(i == j) ans.a[i][j] = 0;
            else ans.a[i][j] = -INF;
        }
    }
    while(k) {
        if(k & 1) ans = ans * a;
        k >>= 1; a = a * a;
    }
    return ans;
}


int tr[maxn][26];
int tot = 0; 
ll w[maxn];           // 结点-->好感度
int fail[maxn];

const int mod = 10007;

void insert(char *s, ll wei)
{ 
    int p = 0;
    for (int i = 0; s[i]; i++)
    {
        int k = s[i] - 'a';
        if (!tr[p][k])
            tr[p][k] = ++tot;   // 根节点为0
        p = tr[p][k];
    }
    w[p] += wei;
}

void build()
{
    queue<int> q;
    memset(fail, 0, sizeof(fail));
    for (int i = 0; i < 26; i++)
        if (tr[0][i])
            q.push(tr[0][i]);

    while (!q.empty())
    {
        int k = q.front(); q.pop();
        for (int i = 0; i < 26; i++)
        {
            if (tr[k][i])
            {
                fail[tr[k][i]] = tr[fail[k]][i];
                q.push(tr[k][i]); //入队
            }
            else
                tr[k][i] = tr[fail[k]][i]; // trie图
        }
    }
}

bool vis[maxn];
ll gao(int u)
{
    if(u == 0) return 0;
    if(vis[u]) return w[u];
    vis[u] = true;
    w[u] += gao(fail[u]);
    return w[u];
}


char t[205]; // 模式串
char s[205];    // 匹配串

ll a[maxn];

int main()
{
    int n;
    ll l;
    cin >> n >> l;
    rep(i, 1, n) {
        scanf("%lld", &a[i]);
    }
    rep(i, 1, n) {
        scanf("%s", t);
        insert(t, a[i]);
    }

    build();

    memset(vis, 0, sizeof(vis));
    rep(i, 1, tot)
        gao(i);
    
    ll li[maxn];
    li[0] = 0;
    rep(i, 1, tot) li[i] = -1;
    Mat X(li, tot + 1, 1);


    Mat Trans;
    Trans.m = Trans.n = tot + 1;
    rep(i, 0, tot)
        rep(j, 0, tot)
            Trans.a[i][j] = -1;
    rep(i, 0, tot) {
        rep(j, 0, 25) {
            Trans.a[tr[i][j]][i] = w[tr[i][j]];
        }
    }

    Mat Ans = Pow(Trans, l) * X;

    ll ans = 0;
    rep(i, 0, tot) {
        ans = max(ans, Ans.a[i][0]);
    }
    printf("%lld", ans);
}
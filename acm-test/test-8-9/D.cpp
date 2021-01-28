#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 50000 + 5;

// 快速幂 计算 a^k % p
// a <= 1e9, k <= 1e9
int Pow(int a, int k, int p) 
{
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

int tr[maxn][26];
int tot = 0; 
int e[maxn];           // 标记字符串结尾
int fail[maxn];

const int mod = 10007;

void insert(char *s)
{ 
    int p = 0;
    for (int i = 0; s[i]; i++)
    {
        int k = s[i] - 'A';
        if (!tr[p][k])
            tr[p][k] = ++tot;   // 根节点为0
        p = tr[p][k];
    }
    // 尾部标记
    e[p]++;
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

int dfs(int u)
{
    if(u == 0) return 0;
    if(e[u]) return 1;
    return e[u] = dfs(fail[u]);
}

int query(char *t)
{
    int p = 0, ans = 0;
    for (int i = 0; t[i]; i++)
    {
        p = tr[p][t[i] - 'a'];
        for (int j = p; j && (e[j] != -1); j = fail[j]) {
            ans += e[j]; 
            e[j] = -1;  // 防止重复遍历
        }
    }
    return ans;
}

void init()
{
    tot = 0;
    memset(tr, 0, sizeof(tr));
    memset(e, 0, sizeof(e));
}

char t[105]; // 模式串
char s[105];    // 匹配串
int dp[105][maxn];   
//  (i,j):长度为i，串尾结点为j的字符串
//  dp的值代表状态空间下，不包含任一模式串的字符串总数
// 图上dp，dp[i+1][next(j)] += dp[i][j];
// 结果：dp[m][0~tot];
// 初始：dp[1][next(0)] += dp[0][0]; // dp[0][0] == 1 

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        scanf("%s", t);
        insert(t);
    }
    build();

    for(int i = 0; i <= tot; i++)
        dfs(i);
    // 去除禁忌结点

    dp[0][0] = 1;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j <= tot; j++) {
            if(e[j]) continue;
            for(int k = 0; k < 26; k++) {
                if(e[tr[j][k]]) continue;
                dp[i + 1][tr[j][k]] = (dp[i + 1][tr[j][k]] + dp[i][j]) % mod; 
            }
        }
    }

    int ans = 0;
    for(int i = 0; i <= tot; i++) {
        ans = (dp[m][i] + ans) % mod;
    }

    int ret = (Pow(26, m, mod) - ans) % mod;
    if(ret < 0) ret += mod;

    cout << ret << endl;
}
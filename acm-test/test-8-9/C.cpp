#include <iostream>
#include <queue>
#include <cstring>
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

int tr[maxn][2];
int tot = 0; 
int e[maxn];           // 标记字符串结尾
int fail[maxn];

const int mod = 10007;

void insert(char *s)
{ 
    int p = 0;
    for (int i = 0; s[i]; i++)
    {
        int k = s[i] - '0';
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
    for (int i = 0; i < 2; i++)
        if (tr[0][i])
            q.push(tr[0][i]);

    while (!q.empty())
    {
        int k = q.front(); q.pop();
        for (int i = 0; i < 2; i++)
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

void tag()
{
    for(int i = 0; i <= tot; i++)
        dfs(i);
}


/*
// dfs环路检测被卡了
bool check(int u) {
    if(e[u]) return false;  // 谔谔
    if(vis[u]) return true; // 产生后向边
    vis[u] = true;
    for(int i = 0; i < 2; i++) {
        if(check(tr[u][i]))
            return true;
    }
    vis[u] = false;
    return false;
}*/

int cnt[maxn];
bool vis[maxn];
bool check() {
    priority_queue<pair<int, int> > q;

    for(int i = 0; i <= tot; i++) {
        if(e[i]) continue;
        for(int j = 0; j < 2; j++) {
            cnt[tr[i][j]]++;    // 入度++
        }
    }

    for(int i = 0; i <= tot; i++) {
        if(e[i] == 0)
            q.push(make_pair(-cnt[i], i));
    }

    q.push(make_pair(0, 0));

    while(!q.empty()) {
        int d = -q.top().first;
        int id = q.top().second;
        q.pop();
        if(vis[id] || e[id]) continue;
        if(d > 0) return true;  // 成环
        vis[id] = true;
        for(int i = 0, nex; i < 2; i++) {
            nex = tr[id][i];
            if(vis[nex] || e[nex]) continue;
            cnt[nex]--;
            q.push(make_pair(-cnt[nex], nex));
        }
    }
    return false;
}

int query(char *t)
{
    int p = 0, ans = 0;
    for (int i = 0; t[i]; i++)
    {
        p = tr[p][t[i] - '0'];
        for (int j = p; j && (e[j] != -1); j = fail[j]) {
            ans += e[j]; 
            e[j] = -1;  // 防止重复遍历
        }
    }
    return ans;
}

char t[30006]; // 模式串
char s[105];    // 匹配串

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        scanf("%s", t);
        insert(t);
    }

    build();

    tag();
    // 去除禁忌结点

    bool ans = check();

    cout << (ans ? "TAK" : "NIE") << endl;
}
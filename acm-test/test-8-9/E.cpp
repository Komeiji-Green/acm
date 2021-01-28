#include <iostream>
#include <queue>
#include <cstring>
#include<algorithm>
using namespace std;
const int maxn = 150000 + 5;

int tr[maxn][100];
int tot = 0; 
int e[maxn];           // 标记字符串结尾:b
int fail[maxn];
int virus[maxn][3];     // 当前串包含病毒标号（不超过3个）

// 33 - 126
const int mod = 10007;

void insert(char *s, int id)
{ 
    int p = 0;
    for (int i = 0; s[i]; i++)
    {
        int k = s[i] - 33;
        if (!tr[p][k])
            tr[p][k] = ++tot;   // 根节点为0
        p = tr[p][k];
    }
    // 尾部标记
    e[p] = id;
}

void build()
{
    queue<int> q;
    memset(fail, 0, sizeof(fail));
    for (int i = 0; i < 94; i++)
        if (tr[0][i])
            q.push(tr[0][i]);

    while (!q.empty())
    {
        int k = q.front(); q.pop();
        for (int i = 0; i < 94; i++)
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
void dfs(int u)
{
    if(u == 0) { vis[u] = true; return; }
    if(vis[u]) return;
    vis[u] = true;
    int f = fail[u], idx = 0;
    dfs(f);
    if(e[u]) virus[u][idx++] = e[u];
    for(int i = 0; i + idx < 3; i++) {
        virus[u][i + idx] = virus[f][i]; 
    }
    return;
}

void tag()
{
    for(int i = 0; i <= tot; i++)
        dfs(i);
}

int web[1005][3];  // 网站所携带病毒

void query(char *t, int id)
{
    int p = 0, idx = 0;
    for (int i = 0; t[i]; i++)
    {
        p = tr[p][t[i] - 33];
        //while(idx < 3 && web[id][idx]) idx++;

        for(int j = 0; j < 3 && virus[p][j]; j++) {
            bool ok = true;
            for(int k = 0; k < idx; k++)
                if(web[id][k] == virus[p][j]) {
                    ok = false; break;
                }
            if(ok && idx < 3) {
                web[id][idx++] = virus[p][j];
            }
        }
    }
}

char t[300];    // 模式串
char s[10010];    // 匹配串

int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        scanf("%s", t);
        insert(t, i);
    }

    build();
    tag();

    int m, cnt = 0;
    cin >> m;
    for(int i = 1; i <= m; i++) {
        scanf("%s", s);
        query(s, i);
        sort(web[i], web[i] + 3);
        bool ok = false;
        for(int j = 0; j < 3; j++) {
            if(web[i][j]) ok = true;
        }
        if(ok) {
            cnt++;
            printf("web %d:", i);
            for(int j = 0; j < 3; j++) {
                if(web[i][j]) printf(" %d", web[i][j]);
            }
            printf("\n");
        }
    }

    printf("total: %d\n", cnt);
}
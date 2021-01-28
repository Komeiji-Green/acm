#include <iostream>
#include <queue>
#include <cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 52333;
const int N = 10000;

/*

多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据
多组数据多组数据多组数据多组数据多组数据多组数据

*/

int tr[maxn][100];
int tot = 0; 
int e[maxn];           // 标记字符串结尾:b
int fail[maxn];
int cnt[maxn];      // 匹配串遍历次数
int ans[N];      // 病毒序列出现次数

const int mod = 10007;

void insert(char *s, int id)
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
    e[p] = id;
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

void duozushuju(char *t)
{
    int p = 0, idx = 0;
    for (int i = 0; t[i]; i++)
    {
        if(t[i] >= 'A' && t[i] <= 'Z') {
            p = tr[p][t[i] - 'A'];
            cnt[p]++;
        } else {
            p = 0;
        }
    }
}

void sum()
{
    for(int i = 0; i <= tot; i++) {
        int num = cnt[i];
        for(int j = i; j; j = fail[j]) {
            if(e[j]) ans[e[j]] += num;
        }
    }
}

char t[1005][100];    // 模式串
char s[2000000 + 105];    // 匹配串

int main()
{
    int n;
    while(scanf("%d", &n) != EOF) {

        tot = 0;
        memset(tr, 0, sizeof(tr));
        memset(e, 0, sizeof(e));
        memset(cnt , 0, sizeof(cnt));
        memset(ans, 0, sizeof(ans));

        for(int i = 1; i <= n; i++) {
            scanf("%s", t[i]);
            insert(t[i], i);
        }

        build();

        scanf("%s", s);
        duozushuju(s);
        sum();

        for(int i = 1; i <= n; i++) {
            if(ans[i])
                printf("%s: %d\n", t[i], ans[i]);
        }
    }
}
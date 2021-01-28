#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 500000 + 5;

int tr[maxn][26], tot = 0; 
int e[maxn];           // 标记字符串结尾
int fail[maxn];       

void insert(char *s) { 
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int k = s[i] - 'a';
        if (!tr[p][k])
            tr[p][k] = ++tot;   // 根节点为0
        p = tr[p][k];
    }      
    e[p]++;  // 尾部标记
}

void build() {
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

int query(char *t) {
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

char t[55]; // 模式串
char s[1000005];    // 匹配串
int main()
{
    int T;
    cin >> T;
    while(T--) {
        init();

        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
            scanf("%s", t);
            insert(t);
        }

        build();

        scanf("%s", s);
        cout << query(s) << endl;
    }
}
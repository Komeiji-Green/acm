#include <iostream>
#include <queue>
using namespace std;
const int N = 1000;
struct AC_automation
{
    int tr[N][26], cnt; //TRIE
    int e[N];           //标记字符串结尾
    int fail[N];        //fail指针

    void insert(char *s)
    { //插入模式串
        int p = 0;
        for (int i = 0; s[i]; i++)
        {
            int k = s[i] - 'a';
            if (!tr[p][k])
                tr[p][k] = ++cnt;
            p = tr[p][k];
        }
        e[p]++;
    }
    void build()
    {
        queue<int> q;
        memset(fail, 0, sizeof(fail));
        for (int i = 0; i < 26; i++)
            if (tr[0][i])
                q.push(tr[0][i]);
        //首字符入队
        //不直接将0入队是为了避免指向自己
        while (!q.empty())
        {
            int k = q.front();
            q.pop(); //当前结点
            for (int i = 0; i < 26; i++)
            {
                if (tr[k][i])
                {
                    fail[tr[k][i]] = tr[fail[k]][i]; //构建当前的fail指针
                    q.push(tr[k][i]);                //入队
                }
                else
                    tr[k][i] = tr[fail[k]][i];
                //匹配到空字符，则索引到父节点fail指针对应的字符，以供后续指针的构建
                //类似并差集的路径压缩，把不存在的tr[k][i]全部指向tr[fail[k]][i]
                //这句话在后面匹配主串的时候也能帮助跳转
            }
        }
    }
    int query(char *t)
    {
        int p = 0, res = 0;
        for (int i = 0; t[i]; i++)
        {
            p = tr[p][t[i] - 'a'];
            for (int j = p; j && ~e[j]; j = fail[j])
                res += e[j], e[j] = -1;
        }
        return res;
    }
};

AC_automation ac;
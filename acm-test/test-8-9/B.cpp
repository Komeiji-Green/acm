#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;
const int maxl = 200000 + 500;
const int N = 10000;

int tr[maxn][100];
int tot = 0; 
int e[maxn];           // 标记字符串结尾:
int l[maxn];
int fail[maxn];

bool vis[maxl];

int cnt[maxl];

int _id[maxl];

const int mod = 10007;

int insert(const string& s, int id, int len)
{ 
    int p = 0;
    for (int i = 0; s[i]; i++)
    {
        int k = (s[i] >= 'a' && s[i] <= 'z' ? s[i] - 'a' : 26);
        if (!tr[p][k])
            tr[p][k] = ++tot;   // 根节点为0
        p = tr[p][k];
    }
    // 尾部标记
    if(e[p] == 0) { e[p] = id; l[p] = len - 1; }
    return e[p];
}

void build()
{
    queue<int> q;
    memset(fail, 0, sizeof(fail));
    for (int i = 0; i < 27; i++)
        if (tr[0][i])
            q.push(tr[0][i]);

    while (!q.empty())
    {
        int k = q.front(); q.pop();
        for (int i = 0; i < 27; i++)
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

int n, q;

/*int f[maxn];    // 路径压缩
int find(int u, int len) {
    if(!u) return 0;
    if(u && e[u] && l[u] <= len)
        return f[u] = u;
    else return f[u] = find(fail[u], len);
}*/

void query(const string& t, int len)
{
    memset(vis, 0, sizeof(bool) * (q + 5));
    int p = 0;
    int sz = (len + 1) * 2;
    for (int i = 0; i < sz; i++)
    {
        int k = (t[i] >= 'a' && t[i] <= 'z' ? t[i] - 'a' : 26);
        p = tr[p][k];

        /*int u = find(p, len);
        for(int j = u; j; j = fail[j]) {
            if(!e[j]) continue;
            if(vis[e[j]]) break;
            vis[e[j]] = true;
            cnt[e[j]]++;
        }*/
        for(int j = p; j; j = fail[j]) {
            if(!e[j]) continue;
            if(vis[e[j]]) break;
            if(l[j] <= len) {
                cnt[e[j]]++;
                vis[e[j]] = true;
            }
        }
    }
}

/*void sum()
{
    for(int i = 0; i <= tot; i++) {
        int num = cnt[i];
        for(int j = i; j; j = fail[j]) {
            if(e[j]) ans[e[j]] += num;
        }
    }
}*/

string s;
string p;
//char w[1000005];
//char buff[100005];
string w[maxl];

struct Arr {
    int sub;
    int len;
};
Arr arr[100005]; 

struct cmp {
    bool operator()(const Arr& lhs, const Arr& rhs) {
        return lhs.len > rhs.len;
    }
};

void init()
{
    tot = 0;
    //memset(f, 0, sizeof(f));
    memset(tr, 0, sizeof(tr));
    memset(e, 0, sizeof(e));
    memset(l, 0, sizeof(l));
    memset(cnt, 0, sizeof(cnt));
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        cin >> n >> q;

        init();

        for(int i = 1; i <= n; i++) {
            cin >> w[i];
            arr[i].len = w[i].size();
            arr[i].sub = i;
            w[i] += '#';
            w[i] += w[i];
        }

        /*for(int i = 1; i <= n; i++) {
            arr[i].sub = strlen(w);
            scanf("%s", buff);
            arr[i].len = strlen(buff);
            strcat(buff, "#");
            strcat(w, buff);
            strcat(w, buff);
        }*/
        for(int i = 1; i <= q; i++) {
            cin >> p >> s;
            s += ("#" + p);
            _id[i] = insert(s, i, s.size());
        }

        build();
        
        //sort(arr + 1, arr + n + 1, cmp());

        /*for(int i = 0; i <= tot; i++)
            f[i] = i;*/

        for(int i = 1; i <= n; i++) {
            query(w[arr[i].sub], arr[i].len);
        }

        for(int i = 1; i <= q; i++) {
            printf("%d\n", cnt[_id[i]]);
        }
    }
}
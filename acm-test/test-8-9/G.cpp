#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
const int maxn = 200000 + 5;
int n, m;

int fa[maxn];   // trie树的父节点
int tr[maxn][26];   // trie树
int tot = 0;

int e[maxn];    // 编号-->结点
int t[maxn];    // 结点-->时间
int L[maxn];    // 结点-->区间 左
int R[maxn];    // 结点-->区间 右

int fail[maxn];
vector<int> ch[maxn];   // fail树的孩子结点
vector<int> ne[maxn];   // Trie树子节点

int insert(const string &s, int p, int id)
{
    for (int i = 0; i < s.size(); i++)
    {
        int k = s[i] - 'a';
        if (!tr[p][k]) { 
            tr[p][k] = ++tot;
            fa[tot] = p; 
            ne[p].push_back(tot);
        }
        p = tr[p][k];
    }
    // id->结点
    return e[id] = p;
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
        int k = q.front();
        q.pop();
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

char op[maxn];
void read()
{
    scanf("%s", op);
    int ptree = 0, pstr = 0, id = 0;
    string s;
    for(int i = 0, c; (c = op[i]); i++) {
        if(c == 'P') {
            ptree = insert(s.substr(pstr), ptree, ++id);
            pstr = s.size();
        } else if (c == 'B') {
            if(s.empty()) continue;
            s.pop_back();
            if(pstr > s.size()) {
                pstr = s.size();
                ptree = fa[ptree];
            }
        } else {
            s.push_back(c);
        }
    }
}


// 获取dfs序
int tm = 0;
void dfs(int u)
{
    L[u] = tm;
    t[u] = tm;
    tm++;
    for(auto nex : ch[u])
        dfs(nex);
    R[u] = tm;
}


void makeFail()
{
    for(int i = 1; i <= tot; i++) {
        ch[fail[i]].push_back(i);
    }
    tm = 0;
    dfs(0);
}


// 树状数组：区间修改，单点查询
int C[maxn];

void add(int id, int val) {
    for(int i = id; i <= tm; i += (i & (-i))) {
        C[i] += val;
    }
}

int query(int id) {
    int ans = 0;
    for(int i = id; i > 0; i -= (i & (-i))) {
        ans += C[i];
    }
    return ans;
}

vector<pair<int, int> > qu[maxn]; 
int ans[maxn]; 
void getans(int u)
{
    //printf("%d ", u);
    if(u != 0) {
        add(t[u], 1);
        for(auto pr : qu[u]) {
            int x = pr.first;
            int i = pr.second;
            ans[i] = query(R[x] - 1) - query(L[x] - 1);
        }
    }
    for(auto nex : ne[u]) {
        getans(nex);
    }
    if(u != 0) {
        add(t[u], -1);
    }
}

int main()
{
    read();
    build();
    makeFail();

    int m;
    cin >> m;
    for(int i = 1, x, y; i <= m; i++) {
        scanf("%d %d", &x, &y);
        qu[e[y]].push_back(make_pair(e[x], i));
    }

    getans(0);
    //cout << endl;

    for(int i = 1; i <= m; i++) {
        printf("%d\n", ans[i]);
    }
}

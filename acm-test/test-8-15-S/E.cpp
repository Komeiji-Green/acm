#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
const int maxn = 500000 + 5;
int n, m;

int fa[maxn];   // trie树的父节点
int tr[maxn][26];   // trie树
int tr2[maxn][26];  // si的trie树
int tot = 0;
int tot2 = 0;

//int e[maxn];    // 编号-->结点
int t[maxn];    // 结点-->时间
int L[maxn];    // 结点-->区间 左
int R[maxn];    // 结点-->区间 右

int fail[maxn];
vector<int> ch[maxn];   // fail树的孩子结点
//vector<int> ne[maxn];   // Trie树子节点

int insert(char *t)
{
    int p = 0;
    for (int i = 0; t[i]; i++)
    {
        int k = t[i] - 'a';
        if (!tr[p][k]) { 
            tr[p][k] = ++tot;
            //fa[tot] = p; 
            //ne[p].push_back(tot);
        }
        p = tr[p][k];
    }
    // id->结点
    return p;
}

int insert2(int p, int c) {
    int k = c - 'a';
    if(!tr2[p][k]) {
        tr2[p][k] = ++tot2;
    }
    p = tr2[p][k];
    return p;
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

struct Query {
    Query(int _id, int _x): id(_id), x(_x) {}
    int id; // 第几个询问
    int x;  // 结点编号
};
vector<Query> qu[maxn]; // 脚标代表着对应的Si在字典树中的位置

int ans[maxn]; 

void getans(int u, int p)
{
    //printf("%d ", u);
    //printf("33\n");
    if(u != 0) {
        for(auto pr : qu[u]) {
            int x = pr.x;
            int id = pr.id;
            ans[id] = query(R[x] - 1) - query(L[x] - 1);
        }
    }
    for(int i = 0; i < 26; i++) {
        if(tr2[u][i]) {
            int nex = tr[p][i];
            if(nex != 0)
                add(t[nex], 1);
            getans(tr2[u][i], nex);
        }
    }
    if(p != 0) {
        add(t[p], -1);
    }
}

int pos[maxn];    // 表示si字典树上的位置

char tstr[maxn];   // 模式串

int main()
{
    int n;
    cin >> n;
    int op, pre;
    char tmp[4];
    rep(i, 1, n) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%s", tmp);
            pos[i] = insert2(0, tmp[0]);
        } else {
            scanf("%d %s", &pre, tmp);
            int p = pos[pre];
            pos[i] = insert2(p, tmp[0]);
        }
    }

    int m;
    cin >> m;
    int si;
    rep(i, 1, m) {
        scanf("%d %s", &si, tstr);
        int x = insert(tstr);
        qu[pos[si]].push_back(Query(i, x));
    }


    build();

    //printf("1\n");

    makeFail();

    //printf("12\n");

    getans(0, 0);
    //printf("123\n");


    rep(i, 1, m) {
        printf("%d\n", ans[i]);
    }
}
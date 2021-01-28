#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int maxn = 100000 * 32 + 100;;
const int INF = 0x7fffffff;

int n;

int f[maxn];    // 父节点
int e[maxn];    // 权值
int val[maxn];  // 路径异或和

/*vector<pair<int, int> > nei[maxn];

int val[maxn];
bool vis[maxn];/*

/*void bfs()
{
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(0);
    val[0] = 0;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        if(vis[cur]) continue;
        vis[cur] = true;
        for(int i = 0; i < nei[cur].size(); i++) {
            if(!vis[nei[cur][i].first]) {
                q.push(nei[cur][i].first);
                val[nei[cur][i].first] = val[cur] ^ nei[cur][i].second;
            }
        }
    }
}*/

void dfs(int i) {
    if(f[i] == i) val[i] = 0;
    else if(val[i] != -1) return;
    else {
        dfs(f[i]);
        val[i] = val[f[i]] ^ e[i];
    }
}

// trie
// trie树本身的思想还是将一个集合视为一个树（通过依次考量不同分量的方式）
// 所以可先将命题转换为集合的形式
struct Node {
    Node() { ch[0] = ch[1] = -1; }
    int ch[2];
};
Node node[maxn];
Node temp[maxn];
int tot = 0;
Node *nil = NULL;

void add(int x) {
    int u = 0;  // 0是根节点
    int d;
    for(int i = 30; i >= 0; i--) {
        d = ((x >> i) & 1);
        if(node[u].ch[d] == -1) node[u].ch[d] = tot++;
        u = node[u].ch[d];
    }
}

int query(int x) {
    int u = 0;
    int d;
    int ans = 0;
    for(int i = 30; i >= 0; i--) {
        d = ((x >> i) & 1);
        if(node[u].ch[d^1] != -1) {
            ans |= (1 << i);
            u = node[u].ch[d^1];
        } else 
            u = node[u].ch[d];
    }
    return ans;
}

int main()
{
    while(scanf("%d", &n) != EOF) {
        int u, v, w;

        for(int i = 0; i < n; i++)
            f[i] = i;
        for(int i = 0; i < n - 1; i++) 
        {
            scanf("%d %d %d", &u, &v, &w);
            if(f[v] == v) { f[v] = u; e[v] = w; } 
            else { f[u] = v; e[u] = w; }
        }

        for(int i = 0; i < n; i++)
            val[i] = -1;
        for(int i = 0; i < n; i++)
            dfs(i);

        /*
        for(int i = 0; i < n - 1; i++) {
            scanf("%d %d %d", &u, &v, &w);
            val[v] = val[u] ^ w;
        }*/


        // 求一个集合中任意两个元素异或和的最大值，和
        // 求一个元素与整个集合的异或和的最大值
        // 有什么本质区别吗？？？？？？
        memcpy(node, temp, sizeof(Node) * 32 * n);
        tot = 0;
        node[tot].ch[0] = node[tot].ch[1] = -1;
        tot++;

        int ans = 0;
        for(int i = 0; i < n; i++) {
            add(val[i]);
            ans = max(ans, query(val[i]));
        }

        printf("%d\n", ans);
    }
}
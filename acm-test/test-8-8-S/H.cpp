#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int maxn = 1000000 + 100;
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
    Node() { ch[0] = ch[1] = NULL; }
    Node(int _bit):bit(_bit) { ch[0] = ch[1] = NULL; }
    Node *ch[2];
    int bit;    // 当前位 0/1
};
Node *nil = NULL;

int main()
{
    while(scanf("%d", &n) != EOF) {
        int u, v, w;

        /*for(int i = 0; i < n; i++)
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
            dfs(i);*/

        for(int i = 0; i < n - 1; i++) {
            scanf("%d %d %d", &u, &v, &w);
            val[v] = val[u] ^ w;
        }

        // 求一个集合中任意两个元素异或和的最大值，和
        // 求一个元素与整个集合的异或和的最大值
        // 有什么本质区别吗？？？？？？

        Node *root = new Node(0);
        int d;
        Node *u1 = root;
        Node *u2 = root;
        int ans = 0, cur = 0;
        for(int i = 0; i < n; i++) {
            u1 = u2 = root;
            cur = 0;
            for(int j = 30; j >= 0; j--) {
                d = ((val[i]>>j) & 1);
                if(u1->ch[d] == nil) u1->ch[d] = new Node(d);
                u1 = u1->ch[d];
                if(u2->ch[d ^ 1] != nil) {
                    cur |= (1<<j);
                    u2 = u2->ch[d^1];
                } else {
                    u2 = u2->ch[d];
                }
            }
            if(cur > ans) ans = cur;
        }

        /*int ans = 0;
        int hbit_ans = 0;
        int cur = 0;
        int hbit_cur = 0;
        for(int i = 0; i < n; i++) {
            Node *u = root;
            cur = 0;
            for(int j = 30; j >= 0; j--) {
                int d = (val[i] & (1 << j)) ? 1 : 0;
                if(u->ch[d ^ 1] != nil) {
                    if(cur == 0) {
                        hbit_cur = j + 1;
                        if(hbit_cur < hbit_ans) break;
                    } 
                    cur += (1 << j);
                    u = u->ch[d ^ 1];
                } else {
                    u = u->ch[d];
                }
            }
            if(cur > ans) { ans = cur; hbit_ans = hbit_cur; }
        }*/
        printf("%d\n", ans);
    }
}
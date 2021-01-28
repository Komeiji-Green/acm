#include<iostream>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;

const int INF = 1000000;
ll gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(int a, int b) { return a / gcd(a, b) * b; }

int n, m;

struct edge {
    edge() {}
    edge(int _u, int _v, int _g, int _l):u(_u), v(_v), gcd(_g), lcm(_l) {}
    int u, v;
    int gcd, lcm;
};

vector<edge> graph[105];

ll mul[106];
ll diver[105];
int cnt[105];

int V[105];
int region[105];    // 联通区域

bool bfs(int i, int num)
{
    bool vis[105] = {};
    int val[105] = {};
    queue<int> q;
    q.push(i);
    val[i] = num;
    while(!q.empty())
    {
        int cur = q.front(); q.pop();
        if(vis[cur]) continue;
        else { vis[cur] = true; region[cur] = true; }
        for(auto e : graph[cur]) {
            int next = e.u;
            if(e.u == cur) next = e.v;
            if((e.lcm % val[cur]) || (val[cur] % e.gcd)) { /*cout << 1 << " " << num << endl;*/ return false; }
            ll nextval = 1ll * e.lcm / val[cur] * e.gcd;
            if(val[next] != 0 && val[next] != nextval) { /*cout << 2 << endl;*/ return false; }
            else if(gcd(val[cur], nextval) != e.gcd) { /*cout << 3 << " " << val[cur] << " " << nextval << endl;*/ return false; }
            else val[next] = nextval;
            q.push(next);
        }
    }
    for(int i = 1; i <= n; i++)
        if(vis[i]) V[i] = val[i];
    return true;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        diver[i] = 1;
        mul[i] = 0;
    }

    int u, v, g, l;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d%d", &u,&v,&g,&l);
        edge e(u, v, g, l);
        graph[u].push_back(e);
        graph[v].push_back(e);
        mul[u] = gcd(l, mul[u]);
        mul[v] = gcd(l, mul[v]);
        diver[u] = lcm(g, diver[u]);
        diver[v] = lcm(g, diver[v]);
    }
    int min_cnt = INF;
    int min_sub = -1;
    for(int i = 1; i <= n; i++) {
        if(mul[i] == 0) cnt[i] = INF;
        else if(mul[i] % diver[i] == 0) cnt[i] = mul[i] / diver[i];
        else { cnt[i] = 0; cout << "NO" << endl; return 0; }
        if(cnt[i] < min_cnt && cnt[i] != 0) min_cnt = cnt[i];
        min_sub = i;
    }

    for(int i = 1; i <= n; i++) {
        if(region[i]) continue;
        bool ok = false;
        for(int j = 1; j <= cnt[i]; j++) {
            if(mul[i] % (j * diver[i]) == 0) {
                if(ok = bfs(i, j * diver[i]))
                    break;
            }
        }
        if(!ok) { 
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    for(int i = 1; i <= n; i++) {
        printf("%d ", V[i]);
    }
    cout << endl;
}
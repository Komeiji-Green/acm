#include<bits/stdc++.h>
#include<vector>
using namespace std;

typedef long long ll;

const int M = 2333333, N = 2333333;
struct Edge {
    int from, to, pre;
} e[M];
int last[N], tot = 0;
void ine(int a, int b) {
    ++tot;
    e[tot].from = a; e[tot].to = b;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b) { ine(a, b); ine(b, a); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

ll sum = 0;
ll dep[N], size[N];
bool leaf[N];
void dfs(int x, int dad, int d) {
    dep[x] = d;
    vector<int> cost;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        dfs(y, x, d + 1);
        cost.push_back(size[y] + 1);
    }
    if(cost.empty()) {
        leaf[x] = true;
        size[x] = 0;
    } else {
        leaf[x] = false;
        sort(cost.begin(), cost.end());
        int sz = cost.size() - 1, i;
        for(i = 0; i < sz; ++i) {
            if(cost[i] < dep[x]) sum -= (dep[x] - cost[i]); 
        }
        size[x] = cost[i];
    }
}
int main() {
    int T, n, cas = 0;
    cin >> T;
    while(T--) {
        ++cas;
        scanf("%d", &n);
        tot = 0;
        for(int i = 0; i <= n; ++i) {
            last[i] = 0;
        }
        for(int i = 2, f; i <= n; ++i) {
            scanf("%d", &f);
            ine2(f, i);
        }
        sum = 0;
        dfs(1, 0, 0);
        for(int i = 1; i <= n; ++i) {
            if(leaf[i]) sum += dep[i];
        }
        printf("Case #%d: %lld\n", cas, sum);
    }
}
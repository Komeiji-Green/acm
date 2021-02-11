#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
struct node {
    int id;
    ll val;
    bool operator<(const node& u) {
        return val < u.val;
    }
} a[maxn];
ll b[maxn];
int f[maxn]; //ll w[maxn];
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
ll cnt = 0;
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    --cnt;
   // w[fy] = max(w[fy], w[fx]);
    f[fx] = fy;
}
vector<int> vec[maxn];
int main() {
    int T;
    cin >> T;
    int n, m;
    while(T--) {
        cin >> n >> m;
        for(int i = 1; i<= n; ++i) f[i] = i;
        for(int i= 1; i <= n; ++i) {
            scanf("%lld", &a[i].val); b[i] = a[i].val;
            a[i].id = i;
        }
        for(int i = 1; i <= n; ++i) vec[i].clear();
        while(m--) {
            int u, v;
            scanf("%d %d", &u, &v);
            vec[u].push_back(v); vec[v].push_back(u);
        }
        sort(a + 1, a + n + 1);
        a[0].val = 0;
        cnt = 0;
        ll sum = 0;
        for(int i = n - 1, j = n; i >= 0; --i) {
            if(i == 0 || a[i].val != a[i+1].val) {
                for(int k = i + 1; k <= j; ++k) {
                    ++cnt;
                    int x = a[k].id;
                    for(auto y : vec[x]) if(b[y] >= b[x]) merge(x, y);
                }
                ll del = a[j].val - a[i].val;
                sum += del * cnt;
                j = i; 
            }
        }
        printf("%lld\n", sum);
    }
}
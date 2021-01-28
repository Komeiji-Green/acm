#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 233333;
ll a[maxn], q[maxn], pre[maxn];
ll h[maxn], ans[maxn];
bool vis[maxn];
struct node {
    int x;
    ll y;
    bool operator<(const node& b) const {
        return y < b.y;
    }
};

struct Heap {
    priority_queue<node> q;
    void push(node v) { q.push(v); }
    void pop() { q.pop(); }
    node top() {
        node res;
        while(!q.empty() && vis[q.top().x]) {
            q.pop();
        }
        if(!q.empty()) res = q.top();
        return res;
    }
} H;

struct Q {
    int id;
    ll q;
    bool operator<(const Q& b) {
        return q > b.q;
    }
} uu[maxn];

ll calc(int i, int j) {
    ll sum = (pre[j] - pre[i-1]);
    if(sum <= 0) return -1;
    return (sum - 1) / (j - i + 1);
}
int nxt[maxn]; ll oo[maxn];
int main() {
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for(int i = 1; i <= m; ++i) {scanf("%lld", &uu[i].q); uu[i].id = i;}
    a[n] = -inf;
    pre[0] = 0;
    for(int i = 1; i <= n; ++i) pre[i] = pre[i-1] + a[i];
    int tot = 0;
    h[++tot] = 1000000000;
    ans[tot] = 0;
    for(int i = 1; i <= n; ++i) {
        nxt[i] = i + 1;
        H.push((node){i, calc(i, i)});
    }
    while(1) {
        node u = H.top(); ll k = u.y; //printf("%d %lld\n", u.x, k);
        H.pop();
        if(k <= 0) break;
        if(h[tot] != k) {
            h[++tot] = k;
            ans[tot] = ans[tot - 1];
        }
        int idx = u.x, i;
        for(i = idx; i <= n; i = nxt[i]) {
            //H.erase((node){i, calc(i, nxt[i] - 1)});
            vis[i] = 1;
            if(calc(idx, nxt[i] - 1) < k) {
                nxt[idx] = nxt[i]; 
                break;
            }
        }
        vis[idx] = 0;
        //if(i == n + 1) return 0;
        ans[tot] = max(ans[tot], (ll)(nxt[idx] - 1 - idx));
        H.push(node{idx, calc(idx, nxt[idx] - 1)});
    }
    h[tot + 1] = 0;
    sort(uu + 1, uu + m + 1);
    for(int i = 1, j = 1; i <= m; ++i) {
        while(uu[i].q <= h[j + 1]) ++j;
        oo[uu[i].id] = ans[j];
    }
    for(int i = 1; i <= m; ++i) {
        printf("%lld ", oo[i]);
    }
    printf("\n");
}
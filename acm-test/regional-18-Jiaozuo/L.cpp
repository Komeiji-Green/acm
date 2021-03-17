#pragma optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9+7;
const int N = 233333;
const int inv24 = 41666667;
const int inv2 = 500000004;
int n, m, d[N], kth[N], rk[N], cnt[N];
vector<int> G[N], vec[N];

inline void add(int &x, int y) {
    (x+=y)>=mod && (x-=mod);
    (x<0) && (x+=mod);
}
int cycle_3() { // b+e
    // G是无向图，G2是定向后的DAG
    int res=0;
    for(int u=1; u<=n; ++u) {
        for(int v : vec[u]) if(v < u) ++cnt[v];
        for(int v : vec[u]) {
            if(v >= u) break;
            for(int w : vec[v])
                if(cnt[w]) {
                    add(res, d[u]+d[v]+d[w]-5);
                }
        }
        for(int v : vec[u]) if(v < u) cnt[v]=0;
    }
    return res;
}
int cycle_4() { // d
    int res=0;
    for(int u=1; u<=n; ++u) {
        int ru = rk[u];
        for(int &v:G2[u])
            for(int &w:G[v])
                if(rk[w]<ru) {
                    add(res, cnt[w]);
                    ++cnt[w];
                }
        for(int &v:G2[u])
            for(int &w:G[v])
                if(rk[w]<ru) 
                    cnt[w]=0;
    }
    return res;
}
int C(int x, int y) {
    if(y==4) return (1ll*x*(x-1)%mod)*(x-2)%mod*(x-3)%mod*inv24%mod;
    else if(y==2) return (1ll*x*(x-1)%mod)*inv2%mod;
    return -1;
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T, u, v;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int i = 1; i <= n; ++i) G[i].clear(), vec[i].clear(), d[i]=0;
        while(m--) {
            cin >> u >> v;
            G[u].push_back(v); G[v].push_back(u);
            d[u]++; d[v]++;
        }
        for(int i = 1; i <= n; ++i) kth[i] = i;
        sort(kth+1, kth+n+1, [&](int x, int y) {return d[x] < d[y];});
        for(int i=1; i<=n; ++i) rk[kth[i]]=i;
        for(int u=1; u<=n; ++u) {
            for(auto v : G[u])
                vec[rk[u]].push_back(rk[v]);
        }
        for(int u=1; u<=n; ++u) sort(vec[u].begin(), vec[u].end());
        int ans=0, cur=0;
        int *deg = d;
        for(int u=1; u<=n; ++u) { // 1
            add(ans, C(deg[u], 4));
            //cout << "C: " << C(deg[u], 4) << endl;
        }
        //cout << "ans: " << ans << endl;
        for(int u=1; u<=n; ++u) {
            for(int v : G[u])
                add(ans, 1ll*C(deg[u]-1, 2)*(deg[v]-1)%mod);
        }
        //cout << "ans: " << ans << endl;
        int c3=cycle_3();
        //cout << "c3: " << c3 << endl;
        add(ans, -3ll*c3%mod);
        //cout << "ans: " << ans << endl;
        for(int u=1; u<=n; ++u) {
            int sum = 0, sq=0;
            for(int v : G[u]) sum+=deg[v]-1, add(sq, 1ll*(deg[v]-1)*(deg[v]-1)%mod);
            sum=1ll*sum*sum%mod;
            add(sum, -sq);
            add(cur, sum);
        }
        cur=1ll*cur*inv2%mod; //2b+c+2d+3e
        add(ans, cur);
        //cout << "ans: " << ans << endl;
        int c4=cycle_4();
        //cout << "c4: " << c4 << endl;
        add(ans, -3ll*c4%mod);
        cout << (ans+mod)%mod << endl;
    }
}


#pragma optimize(2)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int L = 1505;
const int N = 300007;
const ll mod = N;
const int M = L * L;
int cnt[L][L], su[L][L];
ll v[20][L][L];
int n, m;
void getsum1(int a[L][L]) {
    for(int i = 1; i <= m; ++i)
        for(int j = 2; j <= m; ++j)
            a[i][j] += a[i][j-1];
    for(int i = 2; i <= m; ++i)
        for(int j = 1; j <= m; ++j)
            a[i][j] += a[i-1][j];
}
void getsum2(int a[L][L]) {
    for(int i = 1; i <= m; ++i)
        for(int j = 2; j <= m; ++j)
            a[i][j] ^= a[i][j-1];
    for(int i = 2; i <= m; ++i)
        for(int j = 1; j <= m; ++j)
            a[i][j] ^= a[i-1][j];
}
void getsum3(ll a[L][L]) {
    for(int i = 1; i <= m; ++i)
        for(int j = 2; j <= m; ++j)
            a[i][j] += a[i][j-1];
    for(int i = 2; i <= m; ++i)
        for(int j = 1; j <= m; ++j)
            a[i][j] += a[i-1][j];
}

int wei[N]; // 点权
struct Edge {
    int u, v, w; // 边权
    bool operator< (const Edge& b) {
        return u < b.u || u == b.u && v < b.v;
    }
    bool operator== (const Edge& b) {
        return u == b.u && v == b.v;
    }
} e[M];
int tot = 0;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T, l1, r1, l2, r2, x, y, ww, ans, all;
    ll val;
    cin >> T;
    while(T--) {
        cin >> n >> m;

        ans = 0; all = 0; tot = 0;

        for(int i = 1; i <= n; ++i) {
            wei[i] = 0;
        }
        for(int i = 1; i <= m; ++i) 
            for(int j = 1; j <= m; ++j) {
                cnt[i][j] = 0;
                su[i][j] = 0;
                for(int k = 0; k <= 18; ++k)
                    v[k][i][j] = 0;
            }

        for(int i = 1; i <= n; ++i) {
            cin >> l1 >> r1 >> l2 >> r2;
            val = 2 * N + i;
            cnt[l1][l2] += 1;
            cnt[l1][r2+1] -= 1;
            cnt[r1+1][l2] -= 1;
            cnt[r1+1][r2+1] += 1;

            su[l1][l2] ^= i;
            su[l1][r2+1] ^= i;
            su[r1+1][l2] ^= i;
            su[r1+1][r2+1] ^= i;

            for(int j = 0; j <= 18; ++j) {
                if((1<<j)&i) val = i * mod;
                else val = i;
                v[j][l1][l2] += val;
                v[j][l1][r2+1] -= val;
                v[j][r1+1][l2] -= val;
                v[j][r1+1][r2+1] += val;
            }
        }

        getsum1(cnt);
        getsum2(su);
        for(int k = 0; k <= 18; ++k)
            getsum3(v[k]);


        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= m; ++j) {
                if(cnt[i][j]) ++all;
                if(cnt[i][j] == 1) {
                    x = su[i][j];
                    wei[x]++;
                } else if(cnt[i][j] == 2) {
                    x = su[i][j];
                    for(int k = 0; k <= 18; ++k) 
                        if((1<<k)&x) {
                            ++tot;
                            val = v[k][i][j];
                            x = val / mod;
                            y = val % mod;
                            if(x > y) swap(x, y);
                            e[tot].u = x; e[tot].v = y;
                            e[tot].w = 1;
                            break;
                        }
                }
            }
        
        sort(e + 1, e + tot + 1);
        if(tot) {
            int top = 1;
            for(int i = 2; i <= tot; ++i) {
                if(e[i] == e[top]) e[top].w++;
                else e[++top] = e[i];
            }
            tot = top;
        }
        for(int i = 1, uu, vv; i <= tot; ++i) {
            uu = e[i].u; vv = e[i].v;
            ans = max(ans, wei[uu] + wei[vv] + e[i].w);
        }
        
        sort(wei + 1, wei + n + 1);
        ans = max(ans, wei[n] + wei[n-1]);

        cout << (all - ans) << '\n';
    }
}
#pragma optimize(2)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int L = 1505;
const int N = 300007;
const ll mod = N;
const int M = L * L;
int cnt[L][L], su[L][L];
int v[20][L][L];
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

vector<int> G[N];
int vis[N], wei[N];

int main() {

    //clock_t st = clock(), ed;
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T, l1, r1, l2, r2, x, y, ww, ans, all, mx, se, pos, bit;
    ll val;
    cin >> T;
    while(T--) {
        cin >> n >> m;

        ans = 0; all = 0; bit = 0;
        for(int i = 0; i <= 18; ++i) {
            if((1<<i)&n) bit = i;
        }

        for(int i = 1; i <= n; ++i) {
            wei[i] = 0; G[i].clear();
        }
        for(int i = 1; i <= m; ++i) 
            for(int j = 1; j <= m; ++j) {
                cnt[i][j] = 0;
                su[i][j] = 0;
            }
        for(int k = 0; k <= bit; ++k)
            for(int i = 1; i <= m; ++i)
                for(int j = 1; j <= m; ++j)
                    v[k][i][j] = 0;

        for(int i = 1; i <= n; ++i) {
            cin >> l1 >> r1 >> l2 >> r2;
            cnt[l1][l2] += 1;
            cnt[l1][r2+1] -= 1;
            cnt[r1+1][l2] -= 1;
            cnt[r1+1][r2+1] += 1;

            su[l1][l2] ^= i;
            su[l1][r2+1] ^= i;
            su[r1+1][l2] ^= i;
            su[r1+1][r2+1] ^= i;

            for(int j = 0; j <= bit; ++j) {
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
        for(int k = 0; k <= bit; ++k)
            getsum3(v[k]);


        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= m; ++j) {
                if(cnt[i][j]) ++all;
                if(cnt[i][j] == 1) {
                    x = su[i][j];
                    wei[x]++;
                } else if(cnt[i][j] == 2) {
                    x = su[i][j];
                    for(int k = 0; k <= bit; ++k) 
                        if((1<<k)&x) {
                            val = v[k][i][j];
                            x = val / mod;
                            y = val % mod;
                            G[x].push_back(y);
                            G[y].push_back(x);
                            break;
                        }
                }
            }
    
        for(int i = 1; i <= n; ++i) {
            for(auto j : G[i]) ++vis[j];
            for(auto j : G[i]) ans = max(ans, wei[i] + wei[j] + vis[j]), vis[j] = 0;
        }
        
        pos = 0; mx = 0; se = 0;
        for(int i = 1; i <= n; ++i) 
            if(wei[i] >= mx) {
                mx = wei[i];
                pos = i;
            }
        for(int i = 1; i <= n; ++i) {
            if(i != pos && wei[i] >= se) se = wei[i];
        }
        ans = max(ans, mx + se);

        cout << (all - ans) << '\n';
    }

    //ed = clock();
    //cout << (double)(ed-st)/1000 << endl;
}
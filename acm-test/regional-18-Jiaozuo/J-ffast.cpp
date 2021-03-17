#pragma optimize(2)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int L = 1505;
const int N = 300007;
const ll mod = N;
const int M = L * L;
ll cnt[L][L], su[L][L], sq[L][L];
int n, m;
void getsum(ll a[L][L]) {
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
    int T, l1, r1, l2, r2, x, y, ww, ans, all, mx, se, pos;
    ll k, s, del;
    cin >> T;
    while(T--) {
        cin >> n >> m;

        ans = 0; all = 0;

        for(int i = 1; i <= n; ++i) {
            wei[i] = 0; G[i].clear();
        }

        for(int i = 1; i <= m; ++i) 
            for(int j = 1; j <= m; ++j) {
                cnt[i][j] = 0;
                su[i][j] = 0;
                sq[i][j] = 0;
            }

        for(int i = 1; i <= n; ++i) {
            cin >> l1 >> r1 >> l2 >> r2;
            cnt[l1][l2] += 1;
            cnt[l1][r2+1] -= 1;
            cnt[r1+1][l2] -= 1;
            cnt[r1+1][r2+1] += 1;

            su[l1][l2] += i;
            su[l1][r2+1] -= i;
            su[r1+1][l2] -= i;
            su[r1+1][r2+1] += i;

            s = 1ll*i*i;
            sq[l1][l2] += s;
            sq[l1][r2+1] -= s;
            sq[r1+1][l2] -= s;
            sq[r1+1][r2+1] += s;
        }

        getsum(cnt); getsum(su); getsum(sq);


        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= m; ++j) {
                if(cnt[i][j]) ++all;
                if(cnt[i][j] == 1) {
                    x = su[i][j];
                    wei[x]++;
                } else if(cnt[i][j] == 2) {
                    k = su[i][j]; // k
                    s = sq[i][j]; // s
                    del = (ll)(sqrt(2*s-k*k)+0.5);
                    x = (k - del) / 2;
                    y = (k + del) / 2;
                    /*cerr << "i: " << i << " j: " << j << endl;
                    cerr << "x: " << x << " y: " << y << endl;
                    cerr << "k: " << k << " s: " << s << endl;
                    cerr << endl;*/
                    G[x].push_back(y);
                    G[y].push_back(x);
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
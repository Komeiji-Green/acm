#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> vec[55];
ll v[55][5];
ll mm[55][5];

ll maxv = 0;
ll sum[5], tmp;
int m;
void dfs(int k) {
    if(k <= m && vec[k].size()==0) {dfs(k+1); return;}
    tmp = 1;
    for(int j = 0; j < 4; ++j) tmp *= (100 + sum[j] + mm[k][j]);
    if(tmp <= maxv) return;
    if(k > m) {
        maxv = max(maxv, tmp);
        return;
    }
    for(auto x : vec[k]) {
        for(int j = 0; j < 4; ++j) {
            sum[j] += v[x][j];
        }
        dfs(k+1);
        for(int j = 0; j < 4; ++j) {
            sum[j] -= v[x][j];
        }
    }
}
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int i = 1; i <= m; ++i) vec[i].clear();
        for(int i = 1; i <= n; ++i) {
            int t;
            scanf("%d %lld %lld %lld %lld", &t, &v[i][0], &v[i][1], &v[i][2], &v[i][3]);
            vec[t].push_back(i);
        }
        for(int i = 1; i <= m; ++i) {
            for(int j = 0; j < 4; ++j) {
                mm[i][j] = 0;
                for(auto x : vec[i]) {
                    mm[i][j] = max(mm[i][j], v[x][j]);
                }
            }
        }
        for(int j = 0; j < 4; ++j) {
            for(int i = m - 1; i >= 1; --i) {
                mm[i][j] += mm[i+1][j];
            }
        }
        maxv = 0; for(int j = 0; j < 4; ++j) sum[j] = 0;
        dfs(1);
        printf("%lld\n", maxv);
    }
}
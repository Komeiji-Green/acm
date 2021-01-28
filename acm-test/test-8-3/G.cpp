#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
int N, M;


ll list[51][51][4];
ll cnt[51];
ll maxval[51][4];

ll ans = 0;
ll A = 0, B = 0, C = 0, D = 0;

void dfs(int i)
{
    if(i <= 0) {
        ans = max(1ll * (100 + A) * (100 + B) * (100 + C) * (100 + D), ans);
        return;
    }
    if(cnt[i] == 0) { 
        dfs(i - 1);
        return;
    }
    if(1ll * (100 + maxval[i][0] + A) * (100 + maxval[i][1] + B) * (100 + maxval[i][2] + C) * (100 + maxval[i][3] + D) < ans) return;
    for(int j = 0; j < cnt[i]; j++) {
        A += list[i][j][0];
        B += list[i][j][1];
        C += list[i][j][2];
        D += list[i][j][3];
        dfs(i - 1);
        A -= list[i][j][0];
        B -= list[i][j][1];
        C -= list[i][j][2];
        D -= list[i][j][3];
    }
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n, k;
        cin >> n >> k;
        memset(cnt, 0, sizeof(cnt));
        ans = 0;
        A = B = C = D = 0;
        for(int i = 0; i < n; i++) {
            int tp;
            cin >> tp;
            for(int j = 0; j < 4; j++) cin >> list[tp][cnt[tp]][j];
            cnt[tp]++;
        }

        maxval[0][0] = maxval[0][1] = maxval[0][2] = maxval[0][3] = 0;
        for(int i = 1; i <= k; i++) {
            for(int j = 0; j < 4; j++) {
                ll mmax = 0;
                for(int k = 0; k < cnt[i]; k++) {
                    mmax = max(list[i][k][j], mmax);
                }
                maxval[i][j] = maxval[i - 1][j] + mmax;
            }
        }
        dfs(k);
        cout << ans << endl;
    }
}
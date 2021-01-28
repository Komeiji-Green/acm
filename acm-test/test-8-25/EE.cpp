#include<iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int N = 17500;
const int mod = 100000000;

struct Man {
    int L, S;
    ll P;
} man[105];

struct cmp {
    bool operator() (const Man& lhs, const Man& rhs) {
        return lhs.S < rhs.S;
    }
};

ll dp[105][N];
ll cost[N];
inline ll val(int i, int k, int j) {
    return 1ll * min(j - k, man[i].L) * man[i].P;
}

int head = 0, tail = 0;

int main()
{
    //freopen("ff.in", "r", stdin);
    int n, K;
    int test = 1;
    int line = 1;
    cin >> n;
        //printf("line: %d\n", line);
        cin >> K;
        line++;
        memset(dp, 0, sizeof(dp));
        memset(cost, 0, sizeof(cost));
        memset(man, 0, sizeof(man));
        for(int i = 1; i <= K; i++) {
            scanf("%d %lld %d", &man[i].L, &man[i].P, &man[i].S);
            line++;
        }

        sort(man + 1, man + K + 1, cmp());


        for(int i = 1; i <= K; i++) {
            int maxk = 0;
            ll maxv = cost[0] + val(i, 0, man[i].S);
            for(int k = 1; k < man[i].S; k++) {
                ll tmp = cost[k] + val(i, k, man[i].S);
                if(tmp > maxv) {
                    maxv = tmp;
                    maxk = k;
                }
            }
            for(int j = man[i].S, k = maxk; j <= n; j++) {
                if(j >= man[i].S + man[i].L) {
                    dp[i][j] = dp[i][j - 1];
                    cost[j] = max(dp[i][j], cost[j]);
                    continue;
                }
                dp[i][j] = cost[k] + val(i, k, j);
                
                while((k + 1) < man[i].S) {
                    ll nex = cost[k + 1] + val(i, k + 1, j);
                    if(nex < dp[i][j]) break;
                    //printf("%d %d %d: %lld\n", i, k, j, dp[i][j]);
                    dp[i][j] = nex;
                    k++;
                }
                //maxm[j] = max(dp[i][j], maxm[j]);
                cost[j] = max(dp[i][j], cost[j]);
                //printf("%d %d %d: %lld\n", i, k, j, cost[j]);
            }
        }

        /*for(int i = 1; i <= n; i++)
            printf("%d: %lld\n", i, cost[i]);*/

        printf("%lld\n", cost[n]);
        test++;
}
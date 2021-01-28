#include<iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 17500;
const int mod = 100000000;

ll dp[105][N];

struct Man {
    int L, S;
    ll P;
} man[105];

struct cmp {
    bool operator() (const Man& lhs, const Man& rhs) {
        return lhs.S < rhs.S;
    }
};

int main()
{
    int n, K;
    cin >> n >> K;
    for(int i = 1; i <= K; i++) {
        scanf("%d %lld %d", &man[i].L, &man[i].P, &man[i].S);
    }

    sort(man + 1, man + K + 1, cmp());
    man[K + 1].S = n + 1;
    man[0].S = 0;

    for(int i = 1; i <= K; i++) {
        for(int j = man[i].S, k = man[i-1].S; j < man[i + 1].S; j++) {
            if(j >= man[i].S + man[i].L) {
                dp[i][j] = dp[i][j - 1];
                continue;
            }
            dp[i][j] = dp[i-1][k] + 1ll * min(j - k, man[i].L) * man[i].P;
            while((k + 1) < man[i].S) {
                ll nex = dp[i - 1][k + 1] + 1ll * min((j - k - 1), man[i].L) * man[i].P;
                if(nex <= dp[i][j]) break;
                dp[i][j] = nex;
                k++;
            }
        }
    }

    for(int i = 1; i <= K; i++)
        for(int j = man[i].S; j < man[i + 1].S; j++)
            printf("%d %d: %lld\n", i, j, dp[i][j]);

    printf("%lld\n", dp[K][n]);
}


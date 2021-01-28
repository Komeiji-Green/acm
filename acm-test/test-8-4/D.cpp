#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 20000;
int N, M;
int D[maxn];
int W[maxn];
int dp[12881];
int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
        scanf("%d%d", &W[i], &D[i]);
    for(int i = 1; i <= N; i++) 
        for(int j = M; j >= 0; j--)
            if(j - W[i] >= 0)
                dp[j] = max(dp[j - W[i]] + D[i], dp[j]);

    cout << dp[M] << endl;
}
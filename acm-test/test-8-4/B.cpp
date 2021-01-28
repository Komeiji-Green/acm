#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;

ll dp[maxn];
ll C[maxn];
ll Y[maxn];


int main()
{
    int n, S;
    cin >> n >> S;
    for(int i = 0, c, y; i < n; i++)
    {
        scanf("%d%d", &c, &y);
        C[i] = c - S * i;
        Y[i] = y;
    }

    dp[0] = C[0];
    for(int i = 1; i < n; i++) {
        dp[i] = min(dp[i - 1], C[i]);
    }

    ll sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += (dp[i] + S * i) * Y[i];
    }

    cout << sum << endl;
}
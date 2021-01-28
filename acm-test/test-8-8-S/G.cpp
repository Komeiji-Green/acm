#include<iostream>
#include<cstring>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 200000;
int dp[maxn];

char s[maxn][15];


int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            scanf("%s", s[i]);

        dp[1] = 1;
        dp[0] = 1;
        for(int i = 2; i <= n; i++) {
            if(strcmp(s[i], s[i - 1]) == 0) {
                dp[i] = dp[i - 1] % mod;
            } else {
                dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
            }
        }

        cout << dp[n] << endl;
    }
}
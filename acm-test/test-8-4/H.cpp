#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 233;
int a[maxn];
int pre[maxn]; // 前缀和（mod p）
int f[maxn]; // 前一个与其模p同余的前缀和的下标
int sub[maxn]; 

int dp[maxn];


int n;
int p;

int main()
{
    int T;
    cin >> T;
    while(T--) {
        scanf("%d%d", &n, &p);
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        pre[0] = 0;
        sub[0] = 0;
        for(int i = 1; i < p; i++) 
            sub[i] = -1;
        for(int i = 1; i <= n; i++) {
            pre[i] = (pre[i - 1] + a[i]) % p;
            f[i] = sub[pre[i]];
            sub[pre[i]] = i;
        }

        dp[0] = 0;
        for(int i = 1; i <= n; i++) {
            if(f[i] != -1)
                dp[i] = max(dp[f[i]] + 1, dp[i - 1]);
            else
                dp[i] = dp[i - 1];
        }
        /*for(int i = 0; i <= n; i++)
            cout << dp[i] << " ";
        cout << endl;*/
        cout << dp[n] << endl;
    }
}
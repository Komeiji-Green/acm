#include<iostream>
#include<set>
#include<algorithm>
using namespace std;

const int N = 300500;
const int INF = 0x3f3f3f3f;
int a[N], dp[N];
int q[N], hd, tl;
int qq[N], hdd, tll;
//multiset<int> tr, trr;
int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    dp[1] = 0;
    q[tl++] = 1;
    qq[tll++] = 1;
    //tr.insert(dp[1]);
    //trr.insert(dp[1]);
    for(int i = 2; i <= n; i++) {
        int dp1 = INF, maxh = 0;
        while(hd < tl && a[q[tl - 1]] <= a[i]) {
            if(maxh < a[i]) {
                dp1 = min(dp1, dp[q[tl - 1]] + 1);
            }
            maxh = a[q[tl - 1]];
            tl--;
        }
        if(hd < tl && maxh < a[i]) {
            dp1 = min(dp1, dp[q[tl - 1]] + 1);
        }
        q[tl++] = i;
        int minh = INF;
        while(hdd < tll && a[qq[tll - 1]] >= a[i]) {
            if(minh > a[i]) {
                dp1 = min(dp1, dp[qq[tll - 1]] + 1);
            }
            minh = a[qq[tll - 1]];
            tll--;
        }
        if(hdd < tll && minh > a[i]) {
            dp1 = min(dp1, dp[qq[tll - 1]] + 1);
        }
        qq[tll++] = i;
        dp[i] = dp1;
    }
    printf("%d\n", dp[n]);
    //printf("%d\n", dp[n]);
}
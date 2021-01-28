#include<iostream>
#include<string>
using namespace std;

/*
动态规划问题：
问题描述：给定长序列s和短序列r1、2、3，问s中是否右三个不重合的子序列分别等于r1、2、3
注：子序列，而非子串

子问题是什么：
选取r1、r2、r3的长度为j，k，l的前缀，匹配到长序列s上，是否可匹配？
如果可匹配，则可匹配到s的最小下标是什么？
具体地，（所有匹配方案在s中下标最大值）的最小值是什么？

于是定义dp(i, j, k) 表示r1,r2,r3的长为i,j,k的前缀在s中所匹配到的最小下标
如果dp值为n,代表方案不可行

此题特点：只需在线更新dp数组，每次续1s时更新dp数组的一个点

状态转移：dp(i, j, k) = min(nex(dp(i - 1, j, k)), nex(dp(i, j - 1, k)), nex(dp(i, j, k - 1)))
每次在线更新前，我们已知(i - 1, j, k) 以内所有状态的dp值
现在要从(i, 0, 0)起向上求解……
*/

string s;
string r[4];

int n;
const int maxn = 255;
int nex[100000 + 5][26];    
int dp[maxn][maxn][maxn];   

void upd(int tp)
{
    char c = r[tp].back();
    int sub[4];
    for(int i = 1; i <= 3; i++)
        sub[i] = r[i].size();
    int I = sub[1], J = sub[2], K = sub[3];
    sub[tp]--;
    int idx1 = dp[0][sub[2]][sub[3]];
    
    while(idx < n) {
        idx = nex[idx][c];
    }

}

int main()
{
    int q;
    cin >> n >> q;
    cin >> s;

    int cur[26];    // 当前脚标
    for(int i = 0; i < 26; i++) cur[26] = n;
    for(int i = n - 1; i >= 0; i--) {
        cur[s[i] - 'a'] = i;
        for(int j = 0; j < 26; j++) {
            nex[i][j] = cur[j];
        }
    }   // 预处理

    char op[4], add[4];
    int tp;
    for(int i = 0; i < q; i++) {
        scanf("%d", &tp);
        if(op[0] == '+') {
            scanf("%d %s", &tp, add);
            r[tp] += add[0];
            
            upd(tp);
        }
    }
}
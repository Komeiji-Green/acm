#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 5;
int sub[maxn]; 
// 从第i位置开始的 且为[0 ~ i - 1]序列的子序列 最远的尾后下标， 这个数组是递增的
int dp[maxn];

int main()
{
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    //cout << s.find(s.substr(1).c_str(), 0, 1) << endl;
    for(int p = 0, q = 0; p < s.size(); p++) {
        if(q < p) q = p;
        size_t c;
        while(q < s.size() &&  (c = s.find(s.substr(p, q - p + 1), 0)) != string::npos && c + q - p + 1 <= p)
            q++;
        sub[p] = q;
    }
    /*for(int i = 0; i < n; i++)
        printf("%d ", sub[i]);
    cout << endl;*/
    dp[0] = a;
    for(int i = 1; i < n; i++) {
        int idx = upper_bound(sub, sub + n, i) - sub;
        if(idx <= i)
            dp[i] = min(dp[i - 1] + a, dp[idx - 1] + b);
        else
            dp[i] = dp[i - 1] + a;
    }
    /*for(int i = 0; i < n; i++)
        printf("%d ", dp[i]);
    cout << endl;*/
    cout << dp[n - 1] << endl;
}
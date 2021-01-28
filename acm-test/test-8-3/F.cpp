#include<iostream>
#include<unordered_map>
#include<iomanip>
using namespace std;
typedef long long ll;
// 记忆化搜索，状态压缩
int state[2][7];    // 各血量小兵的数量，0我1敌

// 状态压缩
ll getKey()
{
    ll ans = 0;
    for(int i = 1; i >= 0; i--) {
        for(int j = 1; j <= 6; j++) {
            ans = ans * 6 + state[i][j];
        }
    }
    return ans;
}

unordered_map<ll, double> hashtab;  
// 用数组也可，主要是节省空间
// state的哈希值只能对应一个伤害余额，因此不用加维度

// 状态：damage与state，其中state可以唯一确定出damage的值
double dfs(int damage)
{
    state[0][0] = state[1][0] = 0; // 总数
    for(int i = 0; i < 2; i++)
        for(int j = 1; j <= 6; j++)
            state[i][0] += state[i][j];
    if(state[1][0] == 0) return 1.0;
    if(damage == 0) return 0.0;

    ll key = getKey();
    if(hashtab.find(key) != hashtab.end())
        return hashtab[key];

    int sum = state[0][0] + state[1][0];
    double ans = 0.0;
    for(int i = 0; i < 2; i++) {
        for(int j = 1; j <= 6; j++) {
            if(state[i][j] == 0) continue;
            int cur = state[i][j];
            state[i][j]--; state[i][j - 1]++;
            double rest = dfs(damage - 1);
            ans += (double)cur / (double)sum * rest;
            state[i][j]++; state[i][j - 1]--;
        }
    }
    hashtab[key] = ans;
    return ans;
}

int main()
{
    int n, m, d;
    cin >> n >> m >> d;
    int value;
    for(int i = 0; i < n; i++) {
        cin >> value;
        state[0][value]++;
    }
    for(int i = 0; i < m; i++) {
        cin >> value;
        state[1][value]++;
    }
    cout << fixed << setprecision(8) << dfs(d) << endl;
}
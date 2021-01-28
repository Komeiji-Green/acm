#include<iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int N = 27500;
const int mod = 100000000;

struct Man {
    int L, S;
    int P;
} man[120];

struct cmp {
    bool operator() (const Man& lhs, const Man& rhs) {
        return lhs.S < rhs.S;
    }
};

int dp[105][N];  // 第i个工人涂第j个栅栏
int cost[N];
inline int val(int i, int k, int j) {
    return min(j - k, man[i].L) * man[i].P;
}

// 前i个人，涂到木板j
// 如果第i个人不涂木板j, dp[i][j] = dp[i - 1][j]
// 如果j并非为i第一个涂到的木板，则 dp[i][j] = dp[i][j - 1]
// 剩余的情况，设k为前i - 1个人最后涂到的木板 // 这样讨论的问题：太苛刻，无法刻画“最后涂到”
// 这样讨论j：
// 如果j > S 则dp[i][j] = dp[i][j - 1]，因为S一定被涂到了
// 如果j <= S 则设k为前i - 1个人最后涂到的木板
// dp[i][j] = max(dp[i - 1][k] + (j - k) * P), 其中，j - L <= k < j <= S
// 注意到max(...) = max(dp[i - 1][k] - k * P) + j * P
// 随j变化，k在一个区间中，可维护单调队列来储存区间最值
// 加强：j为i最后一个选到的点

int que[N];
int head = 0, tail = 0;
int main()
{
    //freopen("ff.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        scanf("%d %d %d", &man[i].L, &man[i].P, &man[i].S);
    }
    sort(man + 1, man + m + 1, cmp());

    for(int i = 1; i <= m; i++) {
        head = 0;
        tail = 0;
        que[tail++] = 0;
        for(int j = 1; j <= n; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // 第一步转移：继承之前的答案
            if(j >= man[i].S + man[i].L) {
                continue;
            }
            while(head < tail && que[head] < j - man[i].L) head++;
            if(j < man[i].S) {
                while(head < tail && dp[i - 1][que[tail - 1]] + (j - que[tail - 1]) * man[i].P <= dp[i - 1][j]) 
                    tail--;
                que[tail++] = j;
                continue;   // j为i最后一个选的点
            }
            dp[i][j] = max(dp[i][j], dp[i-1][que[head]] + (j - que[head]) * man[i].P);
        }
    }

    /*for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            printf("%d %d: %lld\n", i, j, dp[i][j]);
        }
    }*/

    printf("%d\n", dp[m][n]);
}

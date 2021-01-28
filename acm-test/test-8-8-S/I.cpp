#include<iostream>
#include<cstring>
using namespace std;

// 条件：至多连续六天不下雨，节日必须晴
// 各地连续六天不下雨 等价于 四角落连续六天不下雨（状态压缩）
// 状态：四角落连续不下雨天数（0~6），当前天数，云块位置
// 状态空间大小：7^4 * 365 * 9 = 7 887 285
// 记忆化 or dp

bool vis[366][9][7][7][7][7];
bool dp[366][9][7][7][7][7];
int dat[366][20];

int n;

inline bool in(int pos) { return pos >= 0 && pos < 9; }

int gao(int pos, int op) {
    switch(op) {
    case 0:
        return pos;
    case 1:
        return (pos % 3) ? pos - 1 : -1;
    case 2:
        return ((pos + 1) % 3) ? pos + 1 : -1;
    case 3:
        return pos - 3;
    case 4:
        return pos + 3;
    case 5:
        return ((pos + 1) % 3) ? -1 : pos - 2;
    case 6:
        return (pos % 3) ? -1 : pos + 2;
    case 7:
        return pos - 6;
    case 8:
        return pos + 6;
    }
    return -1;
}

bool dfs(int cnt, int pos, int a, int b, int c, int d) {
    if(cnt == n) return true;
    if(vis[cnt][pos][a][b][c][d]) return dp[cnt][pos][a][b][c][d];

    bool ans = true;

    int aa = a + 1, bb = b + 1, cc = c + 1, dd = d + 1;
    if(pos == 0) aa = 0;
    else if(pos == 2) bb = 0;
    else if(pos == 6) cc = 0;
    else if(pos == 8) dd = 0;

    if(aa >= 7 || bb >= 7 || cc >= 7 || dd >= 7) ans = false;   //雨天平安

    int pr = pos / 3;
    int pc = pos % 3;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            if(dat[cnt][(pr + i) * 4 + pc + j])
                ans = false;
        }
    }   // 晴天平安

    if(ans) {
        for(int i = 0, nex; i < 9; i++) {
            nex = gao(pos, i);
            if(in(nex)) {
                ans = dfs(cnt + 1, nex, aa, bb, cc, dd);
                if(ans) break;
            }
        }
    }   // 递归平安

    vis[cnt][pos][a][b][c][d] = true;
    dp[cnt][pos][a][b][c][d] = ans;
    return ans;
}
int main()
{
    while(scanf("%d", &n) != EOF && n != 0) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 16; j++) {
                scanf("%d", &dat[i][j]);
            }
        }

        memset(vis, 0, sizeof(vis));
        cout << dfs(0, 4, 0, 0, 0, 0) << endl;
    }
}
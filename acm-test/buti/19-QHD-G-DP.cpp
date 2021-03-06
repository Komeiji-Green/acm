#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int inf = 0x3f3f3f3f;

int sgn(int x) {
    if(x == 0) return 0;
    else return x < 0 ? -1 : 1;
}

char s[13][13];
int a[13][13];
int dp[(1<<24)];
bool vis[(1<<24)];

struct PP {
    int i, val;
};

inline int move(int x, int i) {
    x &= (~(1<<i));
    x |= (1<<(i+1));
    return x;
}

void chk(int &x, int y) {
    if(x > y) x = y;
}

void DP(int n) {
    int st = 0;
    for(int i = 0; i < n; ++i) st |= (1<<i);
    int m = 2 * n;
    for(int i = 0; i < (1<<m); ++i) dp[i] = inf;
    dp[st] = 0; vis[st] = 1;
    PP stk[30]; 
    int bit[30] = {};
    int M = (1<<(n<<1));
    
    for(int x = 0, y, r, c, top; x < M; ++x) {
        if(!vis[x]) continue;
        top = 0;
        for(int i = 0; i < m; ++i) bit[i] = ((x>>i)&1);
        r = 0, c = 0;
        for(int i = m-1; i >= 0; --i) {
            if(bit[i]) ++r;
            else ++c;
            if(i+1<m && bit[i] && !bit[i+1]) {
                stk[++top] = (PP){i, a[r][c]};
            }
        }
        for(int i = 1; i <= top; ++i) {
            y = move(x, stk[i].i);
            chk(dp[y], abs(stk[i].val) + dp[x]);
            vis[y] = 1;
        }
        for(int i = 1; i <= top; ++i) {
            for(int j = i + 1; j <= top; ++j) {
                if(sgn(stk[i].val)*sgn(stk[j].val)<0) {
                    y = move(move(x, stk[i].i), stk[j].i);
                    chk(dp[y], abs(stk[i].val + stk[j].val) + dp[x]);
                }
            }
        }
    }  
}

int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for(int i = 1, tmp; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            scanf("%d", &tmp);
            if(s[i][j] == 'W') a[i][j] = tmp;
            else a[i][j] = -tmp;
        }
    }
    clock_t stt = clock(), ed;
    DP(n);
    ed = clock();
    cout << (double)(ed-stt)/1000 << endl;
    int st = 0;
    for(int i = n; i < 2 * n; ++i) st ^= (1<<i);
    int res = dp[st];
    printf("%d\n", res);
}

/*
12
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
*/
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 500000 + 5;

int tr[maxn][26], tot = 0; 
int e[maxn];           // 标记字符串结尾  

void insert(char *s) { 
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int k = s[i] - 'a';
        if (!tr[p][k])
            tr[p][k] = ++tot;   // 根节点为0
        p = tr[p][k];
    }      
    e[p]++;  // 尾部标记
}

char s[maxn], tmp[3000];
int dp[maxn];

const int mod= 20071027;

int main() {
    int cas = 0;
    while(scanf("%s", s) != EOF) {
        cas++;
        int n = strlen(s);
        int m;
        scanf("%d", &m);

        memset(tr, 0, sizeof(tr));
        tot = 0;
        memset(e, 0, sizeof(e));

        while(m--) {
            scanf("%s", tmp);
            insert(tmp);
        }

        memset(dp, 0, sizeof(dp));
        dp[n] = 1;
        for(int i = n - 1; i >= 0; --i) {
            char *ss = s + i;
            for(int j = 0, p = 0; ss[j]; ++j) {
                int k = ss[j] - 'a';
                int pos = tr[p][k];
                if(!pos) break;
                if(e[pos]) {
                    dp[i] = (dp[i] + dp[i + j + 1]) % mod;
                }
                p = pos;
            }
        }
        printf("Case %d: %d\n", cas, dp[0]);
    }
}
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef long long ll;

const int maxn = 5000000 + 5;

int id[300];
void init() {
    for(int i = '0'; i <= '9'; ++i) {
        id[i] = i - '0';
    }
    for(int i = 'A'; i <= 'Z'; ++i) {
        id[i] = i - 'A' + 10;
    }
    for(int i = 'a'; i <= 'z'; ++i) {
        id[i] = i - 'a' + 36;
    }
}

int tr[maxn][62], tot = 0, orz = 0; 
int e[maxn], sum[maxn];           // 标记字符串结尾  

void insert(char *s) { 
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int k = id[s[i]];
        if (tr[p][k] <= orz)
            tr[p][k] = ++tot;   // 根节点为0
        p = tr[p][k] - orz;
    }      
    e[p]++;
    p = 0;
    for(int i = 0; s[i]; ++i) {
        int k = id[s[i]];
        if(tr[p][k] <= orz) break;
        p = tr[p][k] - orz;
        ++sum[p];
    }
    ++sum[0];
}

char s[2333];
int main() {
    init();
    int n, cas = 0;
    while(scanf("%d", &n) && n) {
        cas++;

        orz = tot;
        memset(e, 0, sizeof(e));
        memset(sum, 0, sizeof(sum));
        //memset(tr, 0, sizeof(tr));

        for(int i = 1; i <= n; ++i) {
            scanf("%s", s);
            insert(s);
        }

        ll cnt = 0;
        int m = tot - orz;
        for(int i = 0; i <= m; ++i) {
            cnt += 1ll * e[i] * (e[i] - 1) / 2;
        }

        cnt += 1ll * sum[0] * (sum[0] - 1) / 2;
        for(int i = 1; i <= m; ++i) {
            cnt += 1ll * sum[i] * (sum[i] - 1);
        }

        printf("Case %d: %lld\n", cas, cnt);
    }

}
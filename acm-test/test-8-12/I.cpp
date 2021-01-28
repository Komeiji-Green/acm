#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 105000;
const int N = 55000;

struct Edge
{
    int from, to, pre;
    ll w;
} e[M];
int last[M];
int tot = 0;

void ine(int a, int b, ll w)
{
    tot++;
    e[tot].from = a;
    e[tot].to = b;
    e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w)
{
    ine(a, b, w);
    ine(b, a, w);
}

#define reg(i, x) for (int i = last[x]; i; i = e[i].pre)

int n, m, clc, low[N], dfn[N];
bool iscut[N];
int sta[N], top = 0;
int bcc[N], nums[N], bccnum = 0;
bool isnt[N];    // 含割点数量是否为1
int temp_cnt[N];    
void tarjan(int cur, int dad)
{
    int child = 0;
    low[cur] = dfn[cur] = ++clc;
    if(dad == 0) sta[++top] = cur;
    reg(i, cur)
    {
        int nex = e[i].to;
        if (!dfn[nex]) { // 树边
            child++;
            sta[++top] = nex; //搜索到的点入栈
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
            if (low[nex] >= dfn[cur]) { // 对应子树成为bcc
                //printf("%d %d\n", nex, low[nex]);
                iscut[cur] = true;
                bccnum++;
                do {
                    bcc[sta[top]] = bccnum;
                    nums[bccnum]++;
                    if(iscut[sta[top]]) { 
                        isnt[bccnum] = true; 
                        temp_cnt[bccnum]++;
                    }
                } while(sta[top--] != nex);
            }
        }
        else if (dfn[nex] < dfn[cur] && nex != dad) { // 回边
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if (dad == 0 && child == 1) { // 对根情况单独讨论
        int cnt = 0;
        reg(i, cur) cnt++;
        if(cnt == 1) bccnum++;
        bcc[cur] = bccnum;
        nums[bccnum]++;
        if(temp_cnt[bccnum] == 1) {
            isnt[bccnum] = false;
            nums[bccnum]--;
        }
    }
}

int f[N], w[N];
int find(int x) { return f[x] == x ? x : (f[x] = find(f[x])); }
void merge(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    f[fx] = fy;
    w[fy] += w[fx];
}

int main()
{
    int test = 0;
    while(scanf("%d", &m) != EOF && m != 0) {
        test++;
        n = m + 1;
        int u, v;

        tot = 0;
        memset(last, 0, sizeof(int) * (2 * m + 100));
        clc = 0;
        memset(low, 0, sizeof(low));
        memset(dfn, 0, sizeof(dfn));
        memset(iscut, 0, sizeof(iscut));
        top = 0;
        bccnum = 0;
        memset(bcc, 0, sizeof(bcc));
        memset(nums, 0, sizeof(nums));
        memset(isnt, 0, sizeof(isnt));
        memset(temp_cnt, 0, sizeof(temp_cnt));

        rep(i, 1, n) f[i] = i;
        rep(i, 1, n) w[i] = 1;

        rep(i, 1, m) {
            scanf("%d %d", &u, &v);
            ine2(u, v, 0);
        }

        tarjan(1, 0);

        ll ans = 0;
        ll sum = 1;
        if(bccnum > 1) {
            rep(i, 1, bccnum) {
                if(!isnt[i]) {
                    sum = 1ll * nums[i] * sum;
                    ans++;
                }
            }
        } else {
            ans = 2;
            sum = 1ll * nums[1] * (nums[1] - 1) / 2;
        }

        printf("bccnum: %d\n", bccnum);
        rep(i, 1, n)
            printf("%d ", bcc[i]);
        printf("\n");
        

        printf("Case %d: %lld %lld\n", test, ans, sum);

    }
}
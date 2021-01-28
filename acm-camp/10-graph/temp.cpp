#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 1145140;
const int N = 1145;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

bool vis[M];    // 边的vis数组
int stk[M][2], top = 0;    // 用于存放欧拉路径
void euler(int x) {
    int cnt = 0;
    reg(i, x) { 
        //int y = e[i].to;
        if(vis[i] || vis[i ^ 1]) continue;
        if (cnt == 0) last[x] = i; // 1.下次遇到点x时，直接从边i开始遍历
        cnt++;
        vis[i] = vis[i ^ 1] = 1;
        euler(e[i].to);  // **
        stk[top][0] = x;
        stk[top][1] = e[i].to;
        top++;
        i = last[x];  // 2.跳过在 ** 中已经被遍历过的边，这样才保证时间复杂度是O(E)
    }
}

vector<int> ans[N];

int main() {

    //freopen("tpout.txt", "w", stdout);
    int n;
    cin >> n;
    tot = 1;
    rep(i, 1, n) {
        rep(j, i + 1, n) {
            ine2(i, j, 0);
        }
    }
    if(n & 1) {
        euler(1);
        rep(i, 1, n - 1) {
            printf("%d", stk[top - 1][0]);
            rep(j, 1, i) {
                printf(" %d", stk[top - 1][1]);
                top--;
            }
            printf("\n");
        }
    }
    else {
        int hf = n / 2;
        rep(i, 1, hf) {
            int cur = i, len = n - i;

            ans[len].push_back(cur);
            //printf("%d ", cur);
            rep(j, 1, n - 1) {
                int step = j;
                cur += step * (2 * (j & 1) - 1);
                cur = ((cur % n) + n) % n;
                if(cur == 0) cur = n;

                //printf("%d ", cur);

                if(j <= len) {
                    ans[len].push_back(cur);
                    if(j == len) {
                        ans[n - 1 - len].push_back(cur);
                    }
                } else {
                    ans[n - 1 - len].push_back(cur);
                }
            }
            //printf("\n"); 
        }
        //printf("\n");
        rep(i, 1, n - 1) {
            printf("%d", ans[i][0]);
            rep(j, 1, ans[i].size() - 1) {
                printf(" %d", ans[i][j]);
            }
            printf("\n");
        }
    }
}

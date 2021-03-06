#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll s[50];
ll wei[10][10];
const int N = 50005;
int li[N], n, m;

void change(int *a, int x) {
    int r = 0, c = 0;
    for(int j = 0; j < m; ++j) {
        if((1<<j)&x) {
            a[++r] = c;
        } else {
            ++c;
        }
    }
}

int ichange(int *a) {
    int res = 0, r = 0, c = 0, j = -1;
    a[0] = 0;
    for(int i = 1; i <= n; ++i) {
        j += (a[i] - a[i-1] + 1);
        res |= (1<<j);
    }
    return res;
}

ll dp[2][46][(1<<18)];
struct I {
    int x, y;
    ll w;
    bool operator< (const I& b) {
        return w > b.w;
    }
} uu[100];

void chk(ll &x, ll y) {
    if(x < y) x = y;
}

int pos[50];
ll ans[50];

int main() {
    cin >> n; m = 2 * n;
    for(int i = 1; i <= n; ++i) scanf("%lld", &s[i]);
    for(int i = 1, tmp = 0; i <= n; ++i) {
        ll sum = 0;
        for(int j = i; j <= n; ++j) {
            sum += s[j];
            ++tmp;
            uu[tmp].x = i; uu[tmp].y = j; uu[tmp].w = sum;
        }
    }
    int tot = 0;
    int sz = (1<<m);
    for(int i = 0; i < sz; ++i) {
        int cnt = 0;
        for(int j = 0; j < m; ++j) {
            if((1<<j)&i) ++cnt;
        }
        if(cnt == n) li[++tot] = i;
    }
    int st = 0;
    int num = n * (n + 1) / 2;
    sort(uu + 1, uu + num + 1);
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j <= num; ++j) {
            for(int k = 0; k < sz; ++k) dp[i][j][k] = -1;
        }
    }
    int o = 0;
    for(int j = 0; j < n; ++j) o |= (1<<j);
    dp[st][0][o] = 0;
    int cur, nex, x, y, cnt;
    ll w, cost;
    for(int i = 0; i < num; ++i, st ^= 1) {
        x = uu[i+1].x; y = uu[i+1].y; w = uu[i+1].w;
        for(int j = 0; j <= i; ++j) {
            for(int k = 1; k <= tot; ++k) {
                cur = li[k];
                cost = dp[st][j][cur];
                //chk(ans[j], cost);

                if(cost == -1) continue;
                chk(dp[st^1][j][cur], cost);

                cnt = 0;
                change(pos, cur);
                for(int r = y; r <= n; ++r) {
                    if(pos[r] < x) {
                        cnt += x - pos[r];
                        pos[r] = x;
                    }
                }

                //printf("cnt: %d\n", cnt);
                //printf("wei: %lld\n", w);
                nex = ichange(pos);
                chk(dp[st^1][j+1][nex], cost + w * cnt);

            }
        }
        for(int j = 0; j <= i; ++j) {
            for(int k = 1; k <= tot; ++k) {
                cur = li[k];
                dp[st][j][cur] = -1;
            }
        }
    }
    for(int j = 0; j <= num; ++j) {
        for(int k = 1; k <= tot; ++k) {
            cur = li[k];
            chk(ans[j], dp[st][j][cur]);
        }
    }

    ll sum = 0;
    for(int i = 1; i <= num; ++i) sum += uu[i].w;

    //printf("sum: %lld\n", sum);
    //printf("tot: %d\n", tot);

    for(int i = 1; i <= num; ++i) {
        printf("%lld\n", sum - ans[i]);
    }
}
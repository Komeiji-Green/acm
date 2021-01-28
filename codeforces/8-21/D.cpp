#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 233333;
const int N = 233333;

const ll mod = 1000000007;

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
inline void ine2(int a, int b, ll w) {
    ine(a, b, w); ine(b, a, w);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

ll size[N];    // 子树规模
void change(int x, int dad) {
    size[x] = 1;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        e[i].w = 1;
        change(y, x);
        size[x] += size[y];
    }
}

ll val[N];
ll wei[N];
ll prime[N];

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;

        tot = 0;
        memset(last, 0, sizeof(last));

        int u, v;
        rep(i, 1, n - 1) {
            scanf("%d %d", &u, &v);
            ine2(u, v, 0);
        }

        change(1, 0);

        int num = 0;
        for(int i = 1; i <= tot; i++) {
            if(e[i].w == 0) continue;
            int x = e[i].to;
            val[++num] = size[x] * ((ll)n - size[x]);
            //printf("%d %d: %lld\n", x, e[i].from, val[num]);
        }

        sort(val + 1, val + num + 1, greater<ll>());



        int m;
        cin >> m;
        rep(i, 1, m) {
            scanf("%lld", &prime[i]);
        }

        sort(prime + 1, prime + m + 1, greater<ll>());


        rep(i, 1, num) wei[i] = 1;

        int idx = 1;
        for(idx = 1; idx <= (m - num); idx++) {
            wei[1] = (prime[idx] * wei[1]) % mod;
        }
        rep(i, 1, num) {
            if(idx <= m) {
                wei[i] = (wei[i] * prime[idx]) % mod;
                idx++;
            } else {
                break;
            }
        }

        /*rep(i, 1, num) {
            printf("%lld ", wei[i]);
        }
        printf("\n");*/

        ll ans = 0;
        rep(i, 1, num) {
            ans = (ans + wei[i] * (val[i] % mod) % mod) % mod;
        }

        ans = (ans + mod) % mod;
        printf("%lld\n", ans);
    }
}
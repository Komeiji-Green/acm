#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 23333;

bool isnt[maxn];
int prime[maxn];
int cnt = 0;

int mu[maxn];

// 线性筛求积性函数
void Mu(int n) {
    isnt[1] = true;
    mu[1] = 1;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            //phi[i] = i - 1;
            mu[i] = -1;
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                //phi[x] = phi[i] * prime[j]; 
                mu[x] = 0;
                break;
            } else {
                //phi[x] = phi[i] * (prime[j] - 1);
                mu[x] = -mu[i];
            }
        }
    }
}

// C(n, m)
ll C(int n, int m) {
    ll ans = 1;
    for(int i = 0; i < m; i++) {
        ans = 1ll * ans * (n - i);
    }
    for(int i = 1; i <= m; i++) {
        ans = ans / (1ll * i);
    }
    return ans;
}

int a[maxn];
int m[maxn];
int main()
{
    int n;
    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        memset(m, 0, sizeof(m));
        for(int i = 1; i <= n; i++) {
            int x = a[i];
            int j = 1;
            for(j = 1; j * j < x; j++) {
                if(x % j == 0) {
                    m[j]++;
                    m[x / j]++;
                }
            }
            if(j * j == x) m[j]++;
        }

        Mu(10000);

        ll ans = 0;
        for(int i = 1; i <= 10000; i++) {
            ans += 1ll * mu[i] * C(m[i], 4);
        }

        /*for(int i = 1; i <= 20; i++) {
            printf("%d, m: %d, mu: %d\n", i, m[i], mu[i]);
        }*/

        printf("%lld\n", ans);
    }
}
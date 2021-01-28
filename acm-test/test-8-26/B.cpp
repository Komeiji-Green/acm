#include <iostream>
#include <ctime>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1000000 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛法 [1, n] 内素数
void Prime(int n)
{
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int phi[maxn];
ll pre[maxn];   // 前缀和

// 线性筛求积性函数
void Phi(int n) {
    isnt[1] = true;
    phi[1] = 2;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                phi[x] = phi[i] * prime[j]; 
                break;
            } else {
                phi[x] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    Phi(233333);
    pre[0] = 0;
    for(int i = 1; i <= 233333; i++) {
        pre[i] = phi[i] + pre[i - 1];
    }
    ll K;
    while(scanf("%lld", &K) != EOF && K != 0) {
        int idx = lower_bound(pre, pre + 233333, K) - pre;
        ll b = idx, a;
        ll kk = K - pre[idx - 1];
        for(ll i = 0; i <= b; i++) {
            if(gcd(i, b) == 1) {
                kk--;
                if(!kk) {
                    a = i;
                    break;
                }
            }
        }
        printf("%lld/%lld\n", a, b);
    }
}
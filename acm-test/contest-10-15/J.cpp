#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<unordered_set>
#include<cstring>
#include<cmath>
#include<ctime>
using namespace std;
typedef long long ll;

const int mod = 998244353;
const int maxn = 100000050;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛求积性函数
unordered_map<int, int> mu, ha;
unordered_set<int> uu;
void Sieve(int n) {
    mu[1] = 1;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            if(uu.count(i)) mu[i] = -1;
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                if(uu.count(x)) mu[x] = 0;
                break;
            } else {
                if(uu.count(x)) mu[x] = -mu[i];
            }
        }
    }
}

void InvList(int n, int p)
{
    prime[0] = 0;
    prime[1] = 1;
    for(int i = 2; i <= n; ++i) {
        prime[i] = 1ll * prime[p % i] * (p - p / i) % p;
    }
}

const int N = 10050;
int a[N];

int gao(int d, int n) {
    return (1ll * prime[d] * ha[n / d] % mod) * mu[d];
}
int main() {
    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        scanf("%d", &a[i]);
    }

    clock_t stt = clock(), edd;
    for(int i = 1, j; i <= T; ++i) {
        for(j = 1; j * j < a[i]; ++j) {
            if(a[i] % j == 0) uu.insert(j), uu.insert(a[i] / j);
        }
        if(j * j == a[i]) uu.insert(j);
    }
    Sieve(100000000);
    InvList(100000000, mod);
    int h = 0;

    clock_t st, ed;
    st = clock();
    for(int i = 1; i <= 100000000; ++i) {
        h = (h + prime[i]) % mod;
        if(uu.count(i)) ha[i] = h;
    }
    ed = clock();
    cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
    for(int i = 1, j = 1; i <= T; ++i) {
        int ans = 0;
        if(a[i] == 2) {
            printf("%d\n", (prime[2] + mod) % mod);
        } else {
            for(j = 1; j * j < a[i]; ++j) {
                if(a[i] % j == 0) {
                    ans = (ans + gao(j, a[i])) % mod;
                    ans = (ans + gao(a[i] / j, a[i])) % mod;
                }
            }
            if(j * j == a[i]) ans = (ans + gao(j, a[i])) % mod;
            ans = 1ll * ans * prime[a[i]] % mod;
            ans = (ans + prime[2]) % mod;
            printf("%d\n", (ans + mod) % mod);
        }
    }
    edd = clock();
    cout << (double)(edd - stt) / CLOCKS_PER_SEC << endl;
}
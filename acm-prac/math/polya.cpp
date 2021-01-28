#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int Pow(int a, int k, int p) {
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

const int maxn = 1005;

int p[maxn], l[maxn], cnt = 0;
void Fact(int x) {
    cnt = 0;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            p[cnt] = i; l[cnt] = 0;
            while(x % i == 0) {
                x /= i; 
                l[cnt]++;
            }
            ++cnt;
        }
    }
    if(x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[cnt] = x; l[cnt] = 1; ++cnt;
    }
}

int phi(int x) {
    int ans = x;
    for(int i = 0; i < cnt; ++i) {
        if(x % p[i] == 0) {
            ans /= p[i];
            ans *= (p[i] - 1);
        }
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    int n;
    while(T--) {
        scanf("%d", &n);
        Fact(n);
        int d = 1;
        int ans = 0;
        for(d = 1; 1ll * d * d < n; ++d) {
            if(n % d == 0) {
                ans = (ans + 1ll * phi(n / d) * Pow(n, d, mod) % mod) % mod;
                ans = (ans + 1ll * phi(d) * Pow(n, n / d, mod) % mod) % mod;
            }
        }
        if(1ll * d * d == n) {
            ans = (ans + 1ll * phi(d) * Pow(n, d, mod) % mod) % mod;
        }
        ans = 1ll * ans * Pow(n, mod - 2, mod) % mod;
        printf("%d\n", (ans + mod) % mod);
    }
}
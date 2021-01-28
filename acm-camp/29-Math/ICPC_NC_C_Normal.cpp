#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

// 快速幂 计算 a^k % p
int Pow(int a, int k, int p) {
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

const int mod = 1e9 + 7;

const int maxn = 233333;
char s[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%s", s);
        int len = strlen(s);
        int m = 0;
        for(int i = 0; i < len; ++i) {
            if(s[i] == '1') ++m;
        }

        int cnt = 0;
        for(int i = 0, cur; i < len; ++i) {
            if(s[i] == '1') {
                cur = len - i - 1;
                --m;
                cnt = (cnt + 1ll * Pow(2, cur - m, mod) * Pow(3, m, mod) % mod) % mod;
            }
        }
        cnt = (cnt + 1) % mod;
        printf("%d\n", (cnt + mod) % mod);
    }
}
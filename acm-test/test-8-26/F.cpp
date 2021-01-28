#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

// 快速幂 计算 a^k % p
// a <= 1e9, k <= 1e9
int Pow(int a, int k, int p) 
{
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

const int maxn = 233333;
char s[maxn];

int main()
{
    int phi = mod - 1;
    int pphi = 500000002;
    
    while(scanf("%s", s) != EOF) {
        int len = strlen(s);
        int m = 0;
        for(int i = 0; i < len; i++) {
            m = (1ll * m + 1ll * Pow(10, (len - i - 1) % pphi + pphi, phi) * (s[i] - '0')) % phi;
        }
        m = (1ll * (m - 1) + 1ll * phi) % phi;
        int ans = Pow(2, m, mod);
        printf("%d\n", ans);
    }
}
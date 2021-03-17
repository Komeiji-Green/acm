#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353;
const int N = 6666666;
int inv[N], sum[N];
void init() {
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i < N; ++i) {
        inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    }
    sum[1] = 1;
    for(int i = 2; i < N; ++i) {
        sum[i] = 1ll * inv[i] * inv[i] % mod;
    }
    for(int i = 2; i < N; ++i) sum[i] = (sum[i] + sum[i-1]) % mod;
}
int main() {
    init();
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        int ans = 1ll * sum[n] * inv[n] % mod;
        ans = 3ll * ans % mod;
        printf("%d\n", (ans+mod) %mod);
    }
}
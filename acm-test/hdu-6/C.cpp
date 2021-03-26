#include<bits/stdc++.h>
#include<vector>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const int N = 1000007;
ll p[N], ip[N], inv[N], f2[N];

void init() {
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i < N; ++i) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    p[0] = 1;
    for(int i = 1; i < N; ++i) p[i] = i * p[i-1] % mod;
    ip[0] = 1;
    for(int i = 1; i < N; ++i) ip[i] = inv[i] * ip[i-1] % mod;
    f2[0] = 1;
    for(int i = 1; i < N; ++i) f2[i] = inv[2] * f2[i-1] % mod;
}

ll C(int n, int m) {
    if(m < 0 || m > n) return 0;
    return (p[n]*ip[m]%mod)*ip[n-m]%mod;
} 

ll B(int n, int r) {
    return C(n-1,r-1)*f2[n]%mod;
}

inline void add(ll &x, ll y) {
    x += y;
    (x >= mod) && (x -= mod);
    (x < mod) && (x += mod);
}

int m;
ll E(int x, int y, int z) {
    if(y >= m) {
        return 2ll * (m-z);
    } else {
        ll res = 0;
        int b = m - y, c = m - z;
        for(int t = 1; t < x - m; ++t) {
            add(res, B(t, b)*(E(x-t, m, z+t-b)+t)%mod);
            add(res, B(t, c)*(E(x-t, m, y+t-c)+t)%mod);
        }
        return res;
    }
}
int main() {
    init();
    int T, x, y, z;
    cin >> T;
    while(T--) {
        scanf("%d %d %d", &x, &y, &z);
        if((x+y+z)%3) {
            printf("-1\n");
        } else {
            m = (x+y+z)/3;
            vector<int> tmp{x,y,z};
            sort(tmp.begin(), tmp.end(), greater<int>());
            x = tmp[0], y = tmp[1], z = tmp[2];
            //printf("%d %d %d\n", x, y, z);
            ll res = E(x, y, z);
            printf("%lld\n", (res+mod)%mod);
            
        }
    }
}


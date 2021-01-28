#include<iostream>
using namespace std;
typedef long long ll;

const ll mod = 2147493647;

// 应该是不用慢速乘的，不过保险起见我还是用了
ll multi(ll a, ll k, ll p) {
    ll ans = 0;
    while(k) {
        if(k & 1) ans = (ans + a) % p;
        k >>= 1; a = (a + a) % p; 
    }
    return ans;
}

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

struct Matrix {
    ll a[7][7];
    int m, n;
    Matrix() {}
    Matrix(ll *list, int _m, int _n): 
        m(_m), n(_n) {
        ll * p = list;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                a[i][j] = *p++;
    }
    Matrix multi(const Matrix &rhs, ll p) {
        Matrix ans;
        int s = rhs.n;
        ans.m = m; ans.n = s;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < s; j++) {
                ans.a[i][j] = 0;
                for(int k = 0; k < n; k++) {
                    ans.a[i][j] += 1ll * a[i][k] * rhs.a[k][j] % p;
                    ans.a[i][j] %= p;
                }
            }
        return ans;
    }
};

Matrix Pow(Matrix a, ll k, ll p) {
    ll inilist[49] = {};
    for(int i = 0; i < 7; i++) inilist[i * 7 + i] = 1;
    Matrix ans(inilist, 7, 7);
    while(k) {
        if(k & 1) ans = ans.multi(a, mod);
        k >>= 1; a = a.multi(a, mod);
    }
    return ans;
}

int main()
{
    int T;
    cin >> T;
    ll list[49] = {
        1, 2, 1, 4, 6, 4, 1,
        1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 4, 6, 4, 1,
        0, 0, 0, 1, 3, 3, 1,
        0, 0, 0, 0, 1, 2, 1,
        0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 1
    };
    Matrix Trans(list, 7, 7);
    while(T--) {
        ll n, a1, a2;
        cin >> n >> a1 >> a2;
        ll list2[7] = { a2, a1, 16, 8, 4, 2, 1 };
        Matrix vec2(list2, 7, 1);
        Matrix ans = Pow(Trans, n - 2, mod).multi(vec2, mod);
        printf("%lld\n", (ans.a[0][0] + mod) % mod);
    }
}
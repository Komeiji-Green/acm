#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<ctime>
using namespace std;

const int mod = 998244353;

// 快速幂 计算 a^k % p
int Pow(int a, int k, int p) {
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

struct Matrix {
    int m, n;
    int a[65][65];
    Matrix() {}
    Matrix(int *_li, int _m, int _n) {
        m = _m, n = _n;
        for(int i = 0; i < m; i++) 
            for(int j = 0; j < n; j++)
                a[i][j] = _li[i * n + j];
    }
    static Matrix I(int _n) {
        Matrix ans;
        ans.m = ans.n = _n;
        memset(ans.a, 0, sizeof(ans.a));
        for(int i = 0; i < _n; ++i)
            ans.a[i][i] = 1;
        return ans;
    }
    static Matrix O(int _n) {
        Matrix ans;
        ans.m = ans.n = _n;
        memset(ans.a, 0, sizeof(ans.a));
        return ans;
    }
    Matrix Multi(const Matrix &rhs, int p) {
        Matrix ans;
        ans.m = m;
        ans.n = rhs.n;
        //if(m == 0 || n == 0) printf("!!!\n");
        int nn = rhs.n, sum;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < nn; ++j) {
                sum = 0;
                for(int k = 0; k < n; ++k)
                    sum = (1ll * sum + 1ll * a[i][k] * rhs.a[k][j]) % p;
                ans.a[i][j] = sum;
            }
        return ans;
    }
};
// 矩阵快速幂 (mod p) p <= 1e9
Matrix Pow(Matrix a, int k, int p) {
    Matrix ans = Matrix::I(a.n);
    while(k) {
        if(k & 1) ans = ans.Multi(a, p);
        k >>= 1; a = a.Multi(a, p);
    }
    return ans;
}

bool ban[256];

bool check(int i, int j) {
    // i: 右三位 j: 左三位
    int m = (j * 4) + (i % 4);
    return (i >> 2) == (j % 16) && !ban[m];
}
Matrix getMat() {
    Matrix ans = Matrix::O(64);
    for(int i = 0; i < 64; ++i) {
        for(int j = 0; j < 64; ++j) {
            ans.a[i][j] = check(i, j);
        }
    }
    return ans;
}

Matrix X[64], Y, T[1005], A;

int rn[2005], tot = 0;

const int maxn = 100500;
bool isnt[maxn];
int prime[maxn], S[maxn], SS[maxn], idx[maxn];
int cnt = 0;
void Sieve(int n) {
    isnt[1] = true;
    T[idx[1]] = A;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            if(n % i == 0) {
                T[idx[i]] = Pow(A, i, mod);
                //printf("(%d, %d) ", i, idx[i]);
            }
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(n % x == 0) {
                T[idx[x]] = Pow(T[idx[i]], prime[j], mod);
                //T[idx[x]] = T[idx[i]].Multi(T[idx[prime[j]]], mod);
                //printf("(%d, %d) ", x, idx[x]);
            }
            if(i % prime[j] == 0) break;
        }
    }
}

int main() {
    clock_t st, ed;
    clock_t sst, eed;
    int time_sum = 0;
    int n, m;
    cin >> n >> m;
    memset(ban, 0, sizeof(ban));
    for(int i = 0, a, b, c, d; i < m; ++i) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        ban[a * 64 + b * 16 + c * 4 + d] = true;
    }

    sst = clock();

    for(int i = 1; i <= n; ++i) {
        if(n % i == 0)
            rn[++tot] = i;
    }

    for(int i = 1; i <= tot; ++i) {
        idx[rn[i]] = i;
    }

    A = getMat();

    for(int i = 0; i < 64; ++i) {
        X[i].m = 64, X[i].n = 1;
        X[i].a[i][0] = 1;
    }

    Sieve(n);
    //printf("\n");

    for(int i = 1; i <= tot; ++i) {
        int res = 0;
        for(int j = 0; j < 64; ++j) {
            Y = T[i].Multi(X[j], mod);
            res = (res + Y.a[j][0]) % mod;
        }
        S[rn[i]] = res;
    }

    /*Matrix Ts;
    for(int i = 1; i <= tot; ++i) {
        int res = 0;
        Ts = Pow(A, rn[i], mod);
        for(int j = 0; j < 64; ++j) {
            Y = Ts.Multi(X[j], mod);
            res = (res + Y.a[j][0]) % mod;
        }
        SS[rn[i]] = res;
    }*/

    /*for(int i = 1; i <= tot; ++i) {
        printf("%d %d %d\n", rn[i], SS[rn[i]], S[rn[i]]);
    }*/


    int sum = 0;
    for(int i = 0; i < n; ++i) {
        sum = (sum + S[abs(gcd(i, n))]) % mod;
    }
    sum = 1ll * sum * Pow(n, mod - 2, mod) % mod;

    eed = clock();

    printf("%d\n", (sum + mod) % mod);

    /*sum = 0;
    for(int i = 0; i < n; ++i) {
        sum = (sum + SS[abs(gcd(i, n))]) % mod;
    }
    sum = 1ll * sum * Pow(n, mod - 2, mod) % mod;
    printf("%d\n", (sum + mod) % mod);*/
    //cout << (double)(time_sum) / CLOCKS_PER_SEC << endl;
    //cout << (double)(eed - sst) / CLOCKS_PER_SEC << endl;
}
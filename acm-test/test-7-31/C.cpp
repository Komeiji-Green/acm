#include<iostream>
using namespace std;
typedef long long ll;

struct Matrix {
    int a[2][2];
    Matrix() {}
    Matrix(int a11, int a12, int a21, int a22) {
        a[0][0] = a11; a[0][1] = a12; a[1][0] = a21; a[1][1] = a22;
    }
    Matrix Multi(const Matrix &rhs, int p) {
        Matrix ans;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++) {
                ans.a[i][j] = 0;
                for(int k = 0; k < 2; k++)
                    ans.a[i][j] = (1ll * ans.a[i][j] + 1ll * a[i][k] * rhs.a[k][j]) % p;
            }
        return ans;
    }
};

// 矩阵快速幂 (mod p) p <= 1e9
Matrix Pow(Matrix a, int k, int p) 
{
    Matrix ans(1, 0, 0, 1);
    while(k) {
        if(k & 1) ans = ans.Multi(a, p);
        k >>= 1; a = a.Multi(a, p);
    }
    return ans;
}

// Fibonacci (mod p)
int Fib(int n, int p) {
    if(n == 1) return 3;
    if(n == 2) return 5;
    int f1 = 3;
    int f2 = 5;
    Matrix A(0, 1, 2, 1);
    Matrix T = Pow(A, n - 2, p);
    int fn = (1ll * T.a[1][0] * f1 + 1ll * T.a[1][1] * f2) % p;
    return fn;
}

// an = a(n-1) * 2a(n-2) + 1
// bn = 2 an + 1;
// bn = b(n - 1) + 2* b(n - 2)
int main()
{
    int P = 200907;
    int n;
    while(cin >> n && n) {
        int ans = Fib(n, P);
        cout << 1ll * (ans - 1) * (P - P / 2) % P << endl;
    }
}
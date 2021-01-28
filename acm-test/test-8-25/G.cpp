#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct Mat {
    int m, n;
    double a[4][4];
    Mat() {}
    Mat(double _a[], int _m, int _n) {
        m = _m, n = _n;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                a[i][j] = _a[i * n + j]; 
    }
    Mat mul(const Mat &rhs) {
        Mat ans;
        int p = rhs.n;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < p; j++) {
                ans.a[i][j] = 0;
                for(int k = 0; k < n; k++) {
                    ans.a[i][j] += a[i][k] * rhs.a[k][j];
                }
            }
        }
        ans.m = m;
        ans.n = p;
        return ans;
    }
};

// 矩阵快速幂 (mod p) p <= 1e9
Mat Pow(Mat a, int k) 
{
    double li[4] = {1, 0, 0, 1};
    Mat ans(li, 2, 2);
    while(k) {
        if(k & 1) ans = ans.mul(a);
        k >>= 1; a = a.mul(a);
    }
    return ans;
}

const int N = 100;
int a[N];
int main()
{
    int n;
    while(scanf("%d", &n) != EOF) {
        double p;
        scanf("%lf", &p);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + n + 1);
        int cnt = unique(a + 1, a + n + 1) - a;
        double ans = 1.0;
        int pos = 1;
        for(int i = 1; i < cnt; i++) {
            int k = a[i] - pos;
            if(k == 0) ans *= 0;
            else {
                double li1[2] = {1 - p, 0};
                Mat X(li1, 2, 1);
                double li2[4] = {p, 1 - p, 1, 0};
                Mat T(li2, 2, 2);
                Mat Y = Pow(T, k - 1).mul(X);
                ans *= Y.a[0][0];
                //printf("%d %f %f\n", i, Y.a[0][0], Y.a[1][0]);
            }
            pos = a[i] + 1;
        }
        printf("%.7f\n", fabs(ans));
    }
}
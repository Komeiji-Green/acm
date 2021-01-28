#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>

using namespace std;

typedef long long ll;

// `计算几何模板`
const double eps = 1e-13;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 233333;
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	else return x < 0 ? -1 : 1;
}

double a[maxp];

int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        double l;
        scanf("%d%lf", &n, &l);
        for(int i = 1; i <= n; ++i) {
            scanf("%lf", &a[i]);
        }
        a[0] = 0; a[n + 1] = l;
        double t = 0, v1 = 1, v2 = 1, t1, t2;
        int i = 0, j = n + 1;
        while(i < j) {
            if(i + 1 == j) {
                t += (a[j]-a[i]) / (v1 + v2);
                break;
            }
            t1 = (a[i+1] - a[i]) / v1;
            t2 = (a[j] - a[j-1]) / v2;
            int d = sgn(t1-t2);
            if(d == 0) {
                t += t1;
                ++i; --j;
                v1 += 1; v2 += 1;
            } else if(d < 0) {
                t += t1;
                ++i; v1 += 1;
                a[j] -= t1 * v2;
            } else {
                t += t2;
                --j; v2 += 1;
                a[i] += t2 * v1;
            }
        }
        printf("%.15f\n", t);
    }

}
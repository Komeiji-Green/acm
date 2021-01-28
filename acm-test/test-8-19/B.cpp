#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;

const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 1010;
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	if(x < 0)return -1;
	else return 1;
}
//square of a double
inline double sqr(double x){return x*x;}

int a, b;

double f(double x)
{
    return 2 * b * sqrt(1 - (x * x) / (a * a)); // 写要求辛普森积分的函数，如：椭圆公式 y 表达式
}


double simpson(double a, double b)
{ 
    double c = a + (b - a) / 2;
    return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6;
}
 
double integral(double L, double R) // 自适应辛普森积分
{ 
    double mid = L + (R - L) / 2;
    double ST = simpson(L, R), SL = simpson(L, mid), SR = simpson(mid, R);
    //if(fabs(SL + SR - ST) <= 15 * Eps)  return SL + SR + (SL + SR - ST) / 15; 
    //return integral(L, mid, Eps/2) + integral(mid, R, Eps/2); 
    if(fabs(SL + SR - ST) <= eps) return ST;
    return integral(L, mid) + integral(mid, R);
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        scanf("%d %d", &a, &b);
        double l, r;
        scanf("%lf %lf", &l, &r);
        double ans = integral(l, r);
        printf("%.3f\n", ans);
    }

}
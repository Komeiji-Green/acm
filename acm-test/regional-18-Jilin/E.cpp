#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const double eps = 1e-10;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
double sqr(double x) {
    return x*x;
}
double h;
bool chk(double x) {
    return sgn(x)<=0 && sgn(x+h)>=0;
}
int main() {
    int T;
    double r, x, y, z, vx, vy, vz, a, b, c, A, t, del, t1, t2, z1, z2;
    cin >> T;
    for(int cas = 1; cas <= T; ++cas) {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &r, &h, &x, &y, &z, &vx, &vy, &vz);
        z -= h;
        A = sqr(r)/sqr(h);
        a = sqr(vx)+sqr(vy)-A*sqr(vz);
        b = 2*x*vx+2*y*vy-2*A*z*vz;
        c = sqr(x)+sqr(y)-A*sqr(z);
        del = sqrt(sqr(b)-4*a*c);
        if(sgn(a) == 0) {
            t = -c / b;
        } else {
            t1 = (-b-del)/(2*a);
            t2 = (-b+del)/(2*a);
            if(sgn(t1-t2)>0) swap(t1, t2);
            z1 = z + vz * t1;
            z2 = z + vz * t2;
            vector<double> vec;
            if(chk(z1)) vec.push_back(t1);
            if(chk(z2)) vec.push_back(t2);
            for(double tt : vec) {
                if(sgn(tt)>0) {
                    t = tt; break;
                }
            }
        }
        printf("Case %d: %.10f\n", cas, t);
    }
}
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double ax, ay, bx, by, cx, cy, dx, dy;
int P, Q, R;

inline double dist(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline double gao(double t, double a, double b)
{
    return a * t + b * (1 - t);
}

double EPS = 1e-8;

// (x, y) 到C点时间最小值
double calc(double x, double y) {
    double le = 0.0;
    double ri = 1.0;
    double mid = (le + ri) / 2;
    double mmid = (le + mid) / 2;

    double midx, midy, mmidx, mmidy;
    double midt, mmidt;
    while(ri - le > EPS) {
        midx = gao(mid, cx, dx);
        midy = gao(mid, cy, dy); 
        midt = dist(x, y, midx, midy) / R + dist(midx, midy, dx, dy) / Q;
        mmidx = gao(mmid, cx, dx);
        mmidy = gao(mmid, cy, dy);
        mmidt = dist(x, y, mmidx, mmidy) / R + dist(mmidx, mmidy, dx, dy) / Q;
        if(midt > mmidt)
            ri = mid;
        else {
            le = mmid;
        }
        mid = (le + ri) / 2;
        mmid = (le + mid) / 2;
    }
    return dist(x, y, midx, midy) / R + dist(midx, midy, dx, dy) / Q;
}

int main()
{
    cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;
    cin >> P >> Q >> R;
    double le = 0.0;
    double ri = 1.0;
    double mid = (le + ri) / 2;
    double mmid = (le + mid) / 2;
    double midx, midy, mmidx, mmidy;
    double midt, mmidt;
    while(ri - le > EPS) {
        midx = gao(mid, ax, bx);
        midy = gao(mid, ay, by);
        midt = calc(midx, midy) + dist(ax, ay, midx, midy) / P;
        mmidx = gao(mmid, ax, bx);
        mmidy = gao(mmid, ay, by);
        mmidt = calc(mmidx, mmidy) + dist(ax, ay, mmidx, mmidy) / P;
        if(midt > mmidt)
            ri = mid;
        else {
            le = mmid;
        }
        mid = (le + ri) / 2;
        mmid = (le + mid) / 2;
    }
    cout << fixed << setprecision(2) << calc(midx, midy) + dist(ax, ay, midx, midy) / P << endl;
}
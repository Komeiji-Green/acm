#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

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

inline double sqr(double x){return x*x;}

struct Point {
	double x, y;
};

double Area(Point a, Point b, Point c) {
	return ((b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y));
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;

		double ret_x = 0.0, ret_y = 0.0, area = 0.0;
		Point p0, p1, p2;
        
		scanf("%lf %lf", &p0.x, &p0.y);
		scanf("%lf %lf", &p1.x, &p1.y);

		for(int i = 1; i < n - 1; i++) {
			scanf("%lf %lf", &p2.x, &p2.y);
			double temp = Area(p0, p1, p2);
			//if(sgn(temp) == 0) continue;
			area += temp;
			ret_x += (p0.x + p1.x + p2.x) * temp;
			ret_y += (p0.y + p1.y + p2.y) * temp;
			p1 = p2;
		}
		//double ii = 2.555;
		//printf("%.2f\n", ii);
		printf("%.2f %.2f\n", (ret_x / area / 3), (ret_y / area / 3));
    }
}
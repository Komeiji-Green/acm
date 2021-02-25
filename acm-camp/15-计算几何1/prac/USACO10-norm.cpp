#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// `计算几何模板`
const double eps = 1e-15;
const double inf = 1e20;
const double pi = acos(-1.0);
const int N = 233333;
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	else return x < 0 ? -1 : 1;
}
//square of a double
inline double sqr(double x){return x*x;}

struct Point{
	double x,y, angle;
	Point(){}
	Point(double _x,double _y){
		x = _x;
		y = _y;
	}
	void input(){
		scanf("%lf%lf",&x,&y);
	}
	void output(){
		printf("%.2f %.2f\n",x,y);
	}
	bool operator == (Point b)const{
		return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;
	}
	bool operator < (Point b)const{
		return sgn(angle-b.angle)<0;
	}
	Point operator +(const Point &b)const{
		return Point(x+b.x,y+b.y);
	}
	Point operator -(const Point &b)const{
		return Point(x-b.x,y-b.y);
	}
	//叉积
	double operator ^(const Point &b)const{
		return x*b.y - y*b.x;
	}
	//点积
	double operator *(const Point &b)const{
		return x*b.x + y*b.y;
	}
    Point rotleft() const {
		return Point(-y,x);
	}
    void calangle() {
        angle = atan2(y, x);
    }
};

Point p[N];
ll cnt[N], sum[N];
int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        p[i].input();
        p[i].calangle();
        p[i+n] = p[i];
        p[i+n].angle += 2 * pi;
    }
    int m = 2 * n;
    sort(p, p + m);
    double r;
    for(int i = 0, j = 0; i < n; ++i) {
        r = p[i].angle + pi;
        while(j+1==i || j+1<m&&sgn(p[j+1].angle-r)<0) ++j;
        cnt[i] = j - i;
    }
    for(int i = n; i < m; ++i) cnt[i] = cnt[i-n];
    sum[0] = 0;
    ll s = 0;
    for(int i = 0, j = 0; i < n; ++i) {
        r = p[i].angle + pi;
        if(i) s -= cnt[i];
        while(j+1==i || j+1<m && sgn(p[j+1].angle-r)<0) {
            ++j;
            s += cnt[j];
        }
        sum[i] = s - cnt[i] * (cnt[i]-1) / 2;
    }
    ll ans = 0;
    for(int i = 0; i < n; ++i) ans += sum[i];
    printf("%lld\n", ans/3);

    //for(int i = 0; i < m; ++i) p[i].output();
    //for(int i = 0; i < m; ++i) printf("%d: %lld\n", i, cnt[i]);
    //for(int i = 0; i < n; ++i) printf("%d: %lld\n", i, sum[i]);
}
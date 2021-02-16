#include<bits/stdc++.h>
#include<cmath>
using namespace std;
typedef long long ll;

const double eps = 1e-10;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 1010;
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	else return x < 0 ? -1 : 1;
}
//square of a double
inline double sqr(double x){return x*x;}
struct Point{
	double x,y;
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
		return sgn(x-b.x)== 0?sgn(y-b.y)<0:x<b.x;
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
	//返回长度
	double len(){
		return hypot(x,y);//库函数
	}
	//返回长度的平方
	double len2(){
		return x*x + y*y;
	}
	//返回两点的距离
	double distance(Point p){
		return hypot(x-p.x,y-p.y);
	}
	Point operator +(const Point &b)const{
		return Point(x+b.x,y+b.y);
	}
	Point operator *(const double &k)const{
		return Point(x*k,y*k);
	}
	Point operator /(const double &k)const{
		return Point(x/k,y/k);
	}
	//`计算pa  和  pb 的夹角`
	//`就是求这个点看a,b 所成的夹角`
	//`测试 LightOJ1203`
	double rad(Point a,Point b){
		Point p = *this;
		return fabs(atan2( fabs((a-p)^(b-p)),(a-p)*(b-p) ));
	}
	//`化为长度为r的向量`
	Point trunc(double r){
		double l = len();
		if(!sgn(l))return *this;
		r /= l;
		return Point(x*r,y*r);
	}
	//`逆时针旋转90度`
	Point rotleft(){
		return Point(-y,x);
	}
	//`顺时针旋转90度`
	Point rotright(){
		return Point(y,-x);
	}
	//`绕着p点逆时针旋转angle`
	Point rotate(Point p,double angle){
		Point v = (*this) - p;
		double c = cos(angle), s = sin(angle);
		return Point(p.x + v.x*c - v.y*s,p.y + v.x*s + v.y*c);
	}
};

Point e[3], p[3]; // 法向量
double from[3][2]; // 法向量对应投影值
int main() {
    int T;
    cin >> T;
	double L, d;
	Point o, v;
	const double k = sqrt(3) / 2;
    e[0] = Point(0, 1); e[1] = Point(k, 0.5); e[2] = Point(-k, 0.5); // 法向量
	p[0] = Point(0.5, 0); p[1] = Point(-0.5, 0); p[2] = Point(0, k); // 顶点坐标
	ll K;
    while(T--) {
        scanf("%lf", &L); d = k * L;
		p[0] = Point(0.5 * L, 0); p[1] = Point(-0.5 * L, 0); p[2] = Point(0, k * L);
		o.input(); v.input();
		scanf("%lld", &K);
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j) {
				double pj = e[i] * (p[j]-o);
				if(pj > 0) from[i][1] = pj;
				else from[i][0] = pj;
			}
		}
		double le = 0, ri = 1e12;
		double t = (le + ri) / 2;
		double to, dis; ll cnt;
		for(int i = 0; i < 1000; ++i) {
			cnt = 0;
			for(int j = 0; j < 3; ++j) {
				to = (v * e[j]) * t;
				if(to > 0) dis = fabs(to - from[j][0]);
				else dis = fabs(to - from[j][1]);
				dis = fabs(dis / d);
				cnt += (ll)(dis);
			}
			if(cnt < K) {
				le = t;
			} else {
				ri = t;
			}
			t = (le + ri) / 2;
		}
		/*cnt = 0;
		for(int j = 0; j < 3; ++j) {
			printf("%d: ", j);
			to = (v * e[j]) * t;  
			printf("to = %.8f  from(-) = %.8f  from(+) = %.8f\n", to, from[j][0], from[j][1]);
			
			
			if(to > 0) dis = fabs(to - from[j][1]);
			else dis = fabs(to - from[j][0]);

			printf("dis = %.8f\n", dis);
			dis = fabs(dis / d);
			printf("ddis = %.8f cnt = %lld\n", dis, (ll)dis);
			cnt += (ll)(dis);
		}*/
		printf("%.8f\n", t);
    }	
}
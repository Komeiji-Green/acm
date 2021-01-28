#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

// `计算几何模板`
const double eps = 1e-8;
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

struct Line{
	Point s,e;
	Line(){}
	Line(Point _s,Point _e){
		s = _s;
		e = _e;
	}
	bool operator ==(Line v){
		return (s == v.s)&&(e == v.e);
	}
	//`根据一个点和倾斜角angle确定直线,0<=angle<pi`
	Line(Point p,double angle){
		s = p;
		if(sgn(angle-pi/2) == 0){
			e = (s + Point(0,1));
		}
		else{
			e = (s + Point(1,tan(angle)));
		}
	}
	void input(){
		s.input();
		e.input();
	}
	//求线段长度
	double length(){
		return s.distance(e);
    }
    // 点到直线距离, 退化直线：理解为与p点垂直且过s的直线
    double dispointtoline(Point p){
		return s == e ? p.distance(s) : fabs((p-s)^(e-s))/length();
	}
	//点到线段的距离
	double dispointtoseg(Point p){
		if(sgn((p-s)*(e-s))<0 || sgn((p-e)*(s-e))<0)
			return min(p.distance(s),p.distance(e));
		return dispointtoline(p);
	}
    // 点到线段最大距离
    double maxdispointtoseg(Point p) {
        return max(p.distance(s),p.distance(e));
    }
};

double t1[maxp], t2[maxp];
Point p[maxp], q[maxp], h[maxp];
Line l[maxp];
int tot = 0;
int main() {
    int T;
    cin >> T;
    int cas = 0;
    while(T--) {
        cas++;
        tot = 0;
        int A, B;
        scanf("%d %d", &A, &B);
        for(int i = 1; i <= A; i++) {
            p[i].input();
        }
        for(int i = 1; i <= B; i++) {
            q[i].input();
        }

        double len = 0.0;
        t1[1] = 0;
        for(int i = 2; i <= A; ++i) {
            len += p[i - 1].distance(p[i]);//Len(p[i - 1], p[i]);
            t1[i] = len;
        }
        for(int i = 2; i <= A; ++i) {
            t1[i] /= t1[A];
			//printf("%f\n", t1[i]);
        }
        len = 0.0;
        t2[1] = 0;
        for(int i = 2; i <= B; ++i) {
            len += q[i - 1].distance(q[i]); //Len(q[i - 1], q[i]);
            t2[i] = len;
        }
        for(int i = 2; i <= B; ++i) {
            t2[i] /= t2[B];
        }

        int k1 = 1, k2 = 1;
        h[++tot] = p[k1] - q[k2];
	
		while(k1 < A && k2 < B) {
			int d = sgn(t1[k1 + 1] - t2[k2 + 1]);
			if(d == 0) {
                h[++tot] = p[k1 + 1] - q[k2 + 1];
				++k1; ++k2;
			} else if(d == -1) {
				double t = t1[k1 + 1];
				Point u = q[k2] + (q[k2 + 1] - q[k2]) * ( (t - t2[k2]) / (t2[k2 + 1] - t2[k2]) );
                h[++tot] = p[k1 + 1] - u;
				++k1;
			} else {
				double t = t2[k2 + 1];
				Point u = p[k1] + (p[k1 + 1] - p[k1]) * ( (t - t1[k1]) / (t1[k1 + 1] - t1[k1]) );
                h[++tot] = u - q[k2 + 1];
				++k2;
			}
		}

        for(int i = 1; i < tot; i++) {
            l[i].s = h[i];
            l[i].e = h[i + 1];
        }
        double maxv = 0.0, minv = inf;
        for(int i = 1; i < tot; i++) {
            maxv = max(maxv, l[i].maxdispointtoseg(Point(0,0)));
            minv = min(minv, l[i].dispointtoseg(Point(0,0)));
        }
        printf("Case %d: %.0f\n", cas, fabs(maxv - minv));
    }
}
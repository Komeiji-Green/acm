#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

// `计算几何模板`
const double eps = 1e-10;
const double inf = 1e20;
const double pi = acos(-1.0);
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
		printf("%.6f %.6f",x,y);
	}
	bool operator == (Point b)const{
		return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;
	}
	bool operator < (Point b)const{
		return sgn(x-b.x)== 0?sgn(y-b.y)<0:x<b.x;
	}
    /*bool operator < (Point b)const {
        return x < b.x || x == b.x && y < b.y;
    }*/
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
    // 点在线段上的判断
	bool pointonseg(Point p){
		return sgn((p-s)^(e-s)) == 0 && sgn((p-s)*(p-e)) < 0;
	}
	//`求两直线的交点`
	//`要保证两直线不平行或重合`
	Point crosspoint(Line v){
		double a1 = (v.e-v.s)^(s-v.s);
		double a2 = (v.e-v.s)^(e-v.s);
		return Point((s.x*a2-e.x*a1)/(a2-a1),(s.y*a2-e.y*a1)/(a2-a1));
	}
    bool segcrossseg(Line v){
		int d1 = sgn((e-s)^(v.s-s));
		int d2 = sgn((e-s)^(v.e-s));
		int d3 = sgn((v.e-v.s)^(s-v.s));
		int d4 = sgn((v.e-v.s)^(e-v.s));
        return (d1 ^ d2) == -2 && (d3 ^ d4) == -2;
	}
};

const int maxp = 500;
Point p[maxp * maxp]; int sz = 0;
Line l[maxp];
Point cur[maxp]; int tot = 0;
int main() {
    int n, cas = 0;
    while(scanf("%d", &n) != EOF && n) {
        cas++;
        int cntp = 0, cntq = 0;
        n--;
        sz = 0;
        for(int i = 0; i <= n; i++) {
            p[sz++].input();
        }
        for(int i = 1; i <= n; i++) {
            l[i].s = p[i - 1];
            l[i].e = p[i];
        }
        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                if(l[i].segcrossseg(l[j])) {
                    p[sz++] = l[i].crosspoint(l[j]);
                }
            }
        }
        sort(p, p + sz);
        sz = unique(p, p + sz) - p;
        cntp = sz;
        cntq = n;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < sz; j++) {
                if(l[i].pointonseg(p[j]))
                    cntq++;
            }
        }
        int f = cntq - cntp + 2;
        //printf("p: %d q: %d\n", cntp, cntq);
        printf("Case %d: There are %d pieces.\n", cas, f);
    }
}
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

// `计算几何模板`
const double eps = 1e-13;
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
	double x,y,rad;
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
        return sgn(rad - b.rad) < 0;
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
    double getangle() {
        return atan2(y, x);
    }
};

struct circle{
	Point p;//圆心
	double r;//半径
	circle(){}
	circle(Point _p,double _r){
		p = _p;
		r = _r;
	}
	circle(double x,double y,double _r){
		p = Point(x,y);
		r = _r;
	}
	//输入
	void input(){
		p.input();
		scanf("%lf",&r);
	}
	//输出
	void output(){
		printf("%.2lf %.2lf %.2lf\n",p.x,p.y,r);
	}
	bool operator == (circle v){
		return (p==v.p) && sgn(r-v.r)==0;
	}
	bool operator < (circle v)const{
		return ((p<v.p)||((p==v.p)&&sgn(r-v.r)<0));
	}
	//`点和圆的关系`
	//`0 圆外`
	//`1 圆上`
	//`2 圆内`
	int relation(Point b){
		double dst = b.distance(p);
		if(sgn(dst-r) < 0)return 2;
		else if(sgn(dst-r)==0)return 1;
		return 0;
	}
	//`两圆的关系`
	//`5 相离`
	//`4 外切`
	//`3 相交`
	//`2 内切`
	//`1 内含`
	//`需要Point的distance`
	//`测试：UVA12304`
	int relationcircle(circle v){
		double d = p.distance(v.p);
		if(sgn(d-r-v.r) > 0)return 5;
		if(sgn(d-r-v.r) == 0)return 4;
		double l = fabs(r-v.r);
		if(sgn(d-r-v.r)<0 && sgn(d-l)>0)return 3;
		if(sgn(d-l)==0)return 2;
		if(sgn(d-l)<0)return 1;
	}
	//`求两个圆的交点，返回0表示没有交点，返回1是一个交点，2是两个交点`
	//`需要relationcircle`
	//`测试：UVA12304`
	int pointcrosscircle(circle v,Point &p1,Point &p2){
		int rel = relationcircle(v);
		if(rel == 1 || rel == 5) return 0;
		double d = p.distance(v.p);
		double l = (d*d+r*r-v.r*v.r)/(2*d);
		double h = sqrt(r*r-l*l);
		Point tmp = p + (v.p-p).trunc(l);
		p1 = tmp + ((v.p-p).rotleft().trunc(h));
		p2 = tmp + ((v.p-p).rotright().trunc(h));
		if(rel == 2 || rel == 4)
			return 1;
		return 2;
	}
};

Point p[maxp];
bool check(circle cc[], int n) {
	int last = 0;
	c[last++] = cc[0];
	for(int i = 1; i < n; ++i) {
		int d = cc[i].relationcircle(cc[0]);
		if(d <= 2 && sgn(cc[0].r-cc[i].r) <= 0) return false;
		if(d <= 3) c[last++] = cc[i];
	}
	n = last;
    for(int i = 0; i < n; ++i) {
        int tot = 0;
        for(int j = 0; j < n; ++j) {
            if(j == i) continue;
            if(c[j] == c[i]) {
                if(i == 0) return false;
                continue;
            }
            Point pp[2];
            int cnt = c[i].pointcrosscircle(c[j], pp[0], pp[1]);
            for(int k = 0; k < cnt; ++k) {
                p[++tot] = pp[k];
            }
            for(int k = 1; k <= tot; ++k) {
                p[k].rad = p[k].getangle();
            }
            sort(p + 1, p + tot + 1);
            tot = unique(p + 1, p + tot + 1) - p - 1;
            p[0] = tot ? p[tot] : c[i].p + Point(c[i].r, 0);
        }
        for(int j = 0;)
        
    } 
}

const int maxp = 200;
circle cir[maxp];
int main() {
    int n;
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 1; i <= n; i++) {
            cir[i].input();
        }
        int cnt = 0;
        for(int i = 1; i <= n; i++) {
            cnt += check(cir + i, n - i + 1);
        }
    }
}

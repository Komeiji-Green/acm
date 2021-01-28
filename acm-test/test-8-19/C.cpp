#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;


const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxn = 150000;
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	if(x < 0)return -1;
	else return 1;
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

struct cmp {
    bool operator() (const Point& a, const Point& b) {
        return sgn(a.x-b.x)== 0?sgn(a.y-b.y)<0:a.x<b.x;
    }
};

struct Line {
    double b, c;
    Line() {}
    Line(const Point& A, const Point& B) {
        b = (A.y - B.y) / (A.x - B.x) - (A.x + B.x);
        c = A.y - sqr(A.x) - b * A.x;
    }
    bool operator== (const Line& rhs) {
        return sgn(b == rhs.b) == 0 && sgn(c == rhs.c) == 0;
    }
    int contain(const Point& p) {
        double y0 = sqr(p.x) + b * p.x + c;
        return sgn(p.y - y0);   // 1 表示严格包含 0表示正好在线上 -1表示……
    }
};

Point p[maxn];
Point stk[maxn];
//Line L[maxn];
int n;
int Graham() {
    sort(p, p + n, cmp());
    int cnt = 0;
    for(int i = 0; i < n - 1; i++) {
        if(sgn(p[i].x - p[i + 1].x) == 0) continue;
        p[cnt++] = p[i];
    } // 去重
    p[cnt++] = p[n - 1];

    int top = 0;
    if(cnt <= 1) return 0;
    
    for(int i = 0; i < cnt; i++) {
        while(top > 1 && Line(stk[top - 2], stk[top - 1]).contain(p[i]) >= 0) 
            top--;
        stk[top++] = p[i];
    }
    return top - 1;
}

int main()
{
    int num;
    cin >> num;
    double x, y;
    n = 0;
    for(int i = 0; i < num; i++) {
        scanf("%lf %lf", &x, &y);
        p[n++] = Point(x, y);
    }
    int ans = Graham();
    printf("%d\n", ans);
}


/*void Graham(polygon &convex){
    norm();
    int &top = convex.n;
    top = 0;
    if(n == 1){
        top = 1;
        convex.p[0] = p[0];
        return;
    }
    if(n == 2){
        top = 2;
        convex.p[0] = p[0];
        convex.p[1] = p[1];
        if(convex.p[0] == convex.p[1])top--;
        return;
    }
    convex.p[0] = p[0];
    convex.p[1] = p[1];
    top = 2;
    for(int i = 2;i < n;i++){
        while( top > 1 && sgn((convex.p[top-1]-convex.p[top-2])^(p[i]-convex.p[top-2])) <= 0 )
            top--;
        convex.p[top++] = p[i];
    }
    if(convex.n == 2 && (convex.p[0] == convex.p[1]))convex.n--;//特判
}*/

#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

// `计算几何模板`
const double eps = 1e-9;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 50010;
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

struct polygon{
	int n;
	Point p[maxp];
	void input(int _n){
		n = _n;
		for(int i = 0;i < n;i++) {
			p[i].input();
        }
	}
    void output() {
        for(int i = 0; i < n; ++i) {
            p[i].output();
        }
    }
	void add(Point q){
		p[n++] = q;
	}
	struct cmp{
		Point p;
		cmp(const Point &p0){p = p0;}
		bool operator()(const Point &aa,const Point &bb){
			Point a = aa, b = bb;
			int d = sgn((a-p)^(b-p));
			if(d == 0){
				return sgn(a.distance(p)-b.distance(p)) < 0;
			}
			return d > 0;
		}
	};
	//`进行极角排序`
	//`首先需要找到最左下角的点`
	//`需要重载号好Point的 < 操作符(min函数要用) `
	void norm(){
		Point mi = p[0];
		for(int i = 1;i < n;i++)mi = min(mi,p[i]);
		sort(p,p+n,cmp(mi));
	}
	//`得到凸包`
	//`得到的凸包里面的点编号是0$\sim$n-1的`
	//`两种凸包的方法`
	//`注意如果有影响，要特判下所有点共点，或者共线的特殊情况`
	//`测试 LightOJ1203  LightOJ1239`
	void getconvex(polygon &convex){
		sort(p,p+n);
		convex.n = n;
		for(int i = 0;i < min(n,2);i++){
			convex.p[i] = p[i];
		}
		if(convex.n == 2 && (convex.p[0] == convex.p[1]))convex.n--;//特判
		if(n <= 2)return;
		int &top = convex.n;
		top = 1;
		for(int i = 2;i < n;i++){
			while(top && sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i])) <= 0)
				top--;
			convex.p[++top] = p[i];
		}
		int temp = top;
		convex.p[++top] = p[n-2];
		for(int i = n-3;i >= 0;i--){
			while(top != temp && sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i])) <= 0)
				top--;
			convex.p[++top] = p[i];
		}
		if(convex.n == 2 && (convex.p[0] == convex.p[1]))convex.n--;//特判
		//convex.norm();//`原来得到的是顺时针的点，排序后逆时针`
	}
    //`得到无向面积`
	double getarea(){
		double sum = 0;
		for(int i = 0;i < n;i++){
			sum += (p[i]^p[(i+1)%n]);
		}
		return fabs(sum) / 2;
	}
};

int main() {
    polygon po, con;
    int T, cas = 0;
    cin >> T;
    while(T--) {
        cas++;

        double ans = inf;

        int n;
        scanf("%d", &n);
        po.input(n);
        Point c(0,0);
        for(int i = 0; i < n; ++i) {
            c = c + po.p[i];
        }
        c = c/n;
        po.getconvex(con);
        int m = con.n;

        Point vec, v1, v2, le, ri;
        for(int i = 0; i < m; ++i) {
            ri = con.p[(i+1)%m] - con.p[i];
            le = con.p[((i-1)%m+m)%m] - con.p[i];
            vec = c - con.p[i];
            v1 = vec.rotleft(); v2 = vec.rotright();
            if(sgn(ri ^ v1) > 0 && sgn(v1 ^ le) > 0 ||
                sgn(ri ^ v2) > 0 && sgn(v2 ^ le) > 0) continue;
            ans = min(ans, vec.len());
        }
        for(int i = 0; i < m; ++i) {
            vec = c - con.p[i];
            v2 = (con.p[(i + 1) % m] - con.p[i]).rotleft().trunc(1);
            ans = min(ans, fabs(vec * v2));
        }
        printf("Case #%d: %.3f\n", cas, ans);
    }
}
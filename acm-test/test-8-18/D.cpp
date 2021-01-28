#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

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
//square of a double
inline double sqr(double x){return x*x;}


struct Point{
	double x,y;
    int id;
	Point(){}
	Point(double _x,double _y){
		x = _x;
		y = _y;
	}
    Point(double _x,double _y,int _id){
		x = _x;
		y = _y;
        id = _id;
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
		for(int i = 0;i < n;i++)
			p[i].input();
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
	void norm(int idx){
		Point mi = p[idx];
		sort(p+idx + 1,p+n,cmp(mi));
	}
};

Point a[maxp];
int ans[maxp];
int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        int id;
        double x, y;
        for(int i = 1; i <= n; i++) {
            scanf("%d %lf %lf", &id, &x, &y);
            a[i] = Point(x, y, id);
        }
        for(int i = 2; i <= n; i++) {
            if(a[i].y < a[1].y) swap(a[i], a[1]); 
        }
        polygon pol;
        pol.n = 0;
        for(int i = 1; i <= n; i++) {
            pol.add(a[i]);
        }

        int ansnum = 0;
        for(int i = 0; i < n; i++) {
            ans[++ansnum] = pol.p[i].id;
            pol.norm(i);
        }

        printf("%d ", ansnum);
        for(int i = 1; i <= ansnum; i++) {
            if(i == ansnum) {
                printf("%d\n", ans[i]);
            }
            else printf("%d ", ans[i]);
        }
    }
}

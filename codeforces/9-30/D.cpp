#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

typedef int ll;

const int maxp = 2000 * 2000 + 50;
int sgn(ll x) {
    if(x == 0) return 0;
    else return x < 0 ? -1 : 1;
}
inline double sqr(double x){return x*x;}

struct Point{
	ll x,y;
	Point(){}
	Point(ll _x,ll _y){
		x = _x;
		y = _y;
	}
	void input(){
		scanf("%d%d",&x,&y);
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
	ll operator ^(const Point &b)const{
		return x*b.y - y*b.x;
	}
	//点积
	ll operator *(const Point &b)const{
		return x*b.x + y*b.y;
	}
	//返回长度
	double len(){
		return hypot(x,y);//库函数
	}
	//返回长度的平方
	ll len2(){
		return x*x + y*y;
	}
	//返回两点的距离
	double distance(Point p){
		return hypot(x-p.x,y-p.y);
	}
	Point operator +(const Point &b)const{
		return Point(x+b.x,y+b.y);
	}
	Point operator *(const ll &k)const{
		return Point(x*k,y*k);
	}
	Point operator /(const ll &k)const{
		return Point(x/k,y/k);
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
    void output() {
        for(int i = 0; i < n; ++i) {
            p[i].output();
        }
    }
	void add(Point q){
		p[n++] = q;
	}
	//`得到凸包`
	//`得到的凸包里面的点编号是0$\sim$n-1的`
	//`两种凸包的方法`
	//`注意如果有影响，要特判下所有点共点，或者共线的特殊情况`
	//`测试 LightOJ1203  LightOJ1239`

    void getconvex(polygon &con) {
        sort(p, p + n);
        int &top = con.n;
        top = 0;
        con.p[top++] = p[0];
        for(int i = 1; i < n; ++i) {
            if(sgn(p[i].y-con.p[top-1].y) < 0)
                con.p[top++] = p[i];
        }
        int mm = top;
        top = 0;
        for(int i = 0; i < mm; ++i) {
            if(con.p[i].x <= 0 && con.p[i].y <= 0)
                con.p[top++] = con.p[i];
        }
    }
};

Point p[2005], q[2005]; 
int main() {
    polygon po, con;
    po.n = 0;
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        p[i].input();
    }
    for(int i = 0; i < m; ++i) {
        q[i].input();
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            po.add(p[i] - q[j]);
        }
    }
    po.getconvex(con);

    int cnt = con.n;
    if(cnt == 0) {
        printf("0\n");
    } else {
        int minv = min(1 - con.p[0].x, 1 - con.p[cnt-1].y);
        for(int i = 1; i < cnt; ++i) {
            minv = min(minv, 1 - con.p[i-1].y + 1 - con.p[i].x);
        }
        printf("%d\n", minv);
    }
}
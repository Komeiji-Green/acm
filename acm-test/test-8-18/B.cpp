#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;


const int maxp = 1010;

//`Compares a int to zero`
int sgn(int x){
	if(x == 0) return 0;
	if(x < 0)return -1;
	else return 1;
}


struct Point{
	int x,y;
	Point(){}
	Point(int _x,int _y){
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
	int operator ^(const Point &b)const{
		return x*b.y - y*b.x;
	}
	//点积
	int operator *(const Point &b)const{
		return x*b.x + y*b.y;
	}
	Point operator +(const Point &b)const{
		return Point(x+b.x,y+b.y);
	}
	Point operator *(const int &k)const{
		return Point(x*k,y*k);
	}
	Point operator /(const int &k)const{
		return Point(x/k,y/k);
	}
};

struct Line{
	Point s,e;
	Line(){}
	Line(Point _s,Point _e){
		s = _s;
		e = _e;
	}

	void input(){
		s.input();
		e.input();
	}
	void adjust(){
		if(e < s)swap(s,e);
	}

    // 2 规范相交：穿过
	//`1 非规范相交：端点
	//`0 不相交`
	bool segcrossseg(Line v){
		int d1 = sgn((e-s)^(v.s-s));
		int d2 = sgn((e-s)^(v.e-s));
		int d3 = sgn((v.e-v.s)^(s-v.s));
		int d4 = sgn((v.e-v.s)^(e-v.s));
		if( (d1^d2)==-2 && (d3^d4)==-2 ) return true;
		return (d1==0 && sgn((v.s-s)*(v.s-e))<=0) ||
			(d2==0 && sgn((v.e-s)*(v.e-e))<=0) ||
			(d3==0 && sgn((s-v.s)*(s-v.e))<=0) ||
			(d4==0 && sgn((e-v.s)*(e-v.e))<=0);
	}
};

/*
The input consists of n test cases. The first line of the input file contains the number n. Each following line contains one test case of the format:
xstart ystart xend yend xleft ytop xright ybottom
*/

bool in(Point a, Point c, Point p) {
    return p.x >= a.x && p.x <= c.x && p.y <= a.y && p.y >= c.y;
}
int main()
{
    int T;
    cin >> T;
    while(T--) {
        Line l;
        l.input();
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if(x1 >= x2) swap(x1, x2);
        if(y1 <= y2) swap(y1, y2);
        
        Point a(x1, y1), c(x2, y2);
        Point b(a.x, c.y);
        Point d(c.x, a.y);

        Line l1(a, b), l2(b, c), l3(c, d), l4(d, a);
        bool flag 
        = l.segcrossseg(l1) || l.segcrossseg(l2) || l.segcrossseg(l3) || l.segcrossseg(l4) || 
          in(a, c, l.e) || in(a, c, l.s);
        if(flag) {
            printf("T\n");
        } else {
            printf("F\n");
        }
    }
}
#include<bits/stdc++.h>

using namespace std;

// `计算几何模板`
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int N = 1010;
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	else return x < 0 ? -1 : 1;
}

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
		printf("%.10f %.10f\n",x,y);
	}
	bool operator == (Point b)const{
		return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;
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
    Point trunc(double r){
		double l = len();
		if(!sgn(l))return *this;
		r /= l;
		return Point(x*r,y*r);
	}
};

struct Line {
    Point s, e;
    Line(){}
	Line(Point _s,Point _e){
		s = _s;
		e = _e;
	}
	bool operator ==(Line v){
		return (s == v.s)&&(e == v.e);
	}
    //`点和直线关系`
	//`1  在左侧`
	//`2  在右侧`
	//`3  在直线上`
    int relation(Point p){
		int c = sgn((p-s)^(e-s));
		if(c < 0)return 1;
		else if(c > 0)return 2;
		else return 3;
	}
    //`直线和线段相交判断`
	//`-*this line   -v seg`
	//`2 规范相交`
	//`1 非规范相交`
	//`0 不相交`
	int linecrossseg(Line v){
		int d1 = sgn((e-s)^(v.s-s));
		int d2 = sgn((e-s)^(v.e-s));
		if((d1^d2)==-2) return 2;
		return (d1==0||d2==0);
	}
    //`求两直线的交点`
	//`要保证两直线不平行或重合`
	Point crosspoint(Line v){
		double a1 = (v.e-v.s)^(s-v.s);
		double a2 = (v.e-v.s)^(e-v.s);
		return Point((s.x*a2-e.x*a1)/(a2-a1),(s.y*a2-e.y*a1)/(a2-a1));
	}
    bool parallel(Line v){
		return sgn((e-s)^(v.e-v.s)) == 0;
	}
};

Point p[N], li[N], s, e, v;
Line seg[N], l;
double dis[N], l1, l2, ans = 0.0, cur = 0.0, le, ri;
int n;

bool chk(int i, Point t) {
    Point x = p[i==0?n-1:i-1], y = p[i+1], o = p[i];
    if(sgn((y-o)^(o-x)) > 0) {
        return !(Line(o, y).relation(t) == 2 && Line(x, o).relation(t) == 2);
    } else {
        return !(Line(o, y).relation(t) == 2 || Line(x, o).relation(t) == 2);
    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n; ++i) p[i].input();
    p[n] = p[0];
    for(int i = 0; i < n; ++i) seg[i] = Line(p[i], p[i+1]);
    Point x, y;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            s = p[i]; e = p[j];
            l = Line(s, e);
            v = (e-s).trunc(1);
            int tot = 0;
            for(int k = 0; k < n; ++k) {
                if(l.linecrossseg(seg[k])==2) {
                    li[tot++] = l.crosspoint(seg[k]);
                }
            }
            for(int k = 0; k < n; ++k) {
                if(l.relation(p[k]) == 3) {
                    x = p[k==0?n-1:k-1], y = p[k+1];
                    int rx = l.relation(x), ry = l.relation(y);
                    if(rx == 3 || ry == 3) {
                        if(sgn((y-p[k])^(x-p[k]))>0) li[tot++] = p[k];
                    } else if(rx != ry) {
                        li[tot++] = p[k];
                    }
                }
            }
            bool f = 1;
            if(!chk(j, s)) f = 0;
            if(!chk(i, e)) f = 0;
            le = inf, ri = inf;
            for(int k = 0; k < tot && f; ++k) {
                if(sgn((li[k]-s)*(li[k]-e)) < 0) f = 0;
                else {
                    l1 = li[k].distance(s); l2 = li[k].distance(e);
                    if(sgn(l1 - l2) < 0) {
                        le = min(le, l1);
                    } else {
                        ri = min(ri, l2);
                    }
                }
            }
            //printf("f: %d\n", f);
            //for(int k = 0; k < tot; ++k) li[k].output();
            if(f) ans = max(ans, le + ri + s.distance(e));
            /*
            for(int i = 0; i < tot; ++i) li[i].output();
            printf("\n");
            len = s.distance(e); printf("len: %.16f\n", len);
            for(int k = 0; k < tot; ++k) {
                dis[k] = ((li[k]-s) * v); printf("%.16f\n", dis[k]);
            }
            printf("\n");
            le = -inf, ri = inf;
            bool f = 1;
            for(int k = 0; k < tot && f; ++k) {
                if(sgn(dis[k])<=0) le = max(le, dis[k]);
                else if(sgn(dis[k]-len)<0) f = 0;
                else ri = min(ri, dis[k]);
            }
            if(f) ans = max(ans, ri - le);
            */
        }
    }
    printf("%.9f\n", ans);
}
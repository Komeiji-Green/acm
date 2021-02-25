#include<bits/stdc++.h>
using namespace std;

// `计算几何模板`
const double eps = 1e-15;
const double inf = 1e20;
const double pi = acos(-1.0);
const int N = 233333;
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
	Point operator +(const Point &b)const{
		return Point(x+b.x,y+b.y);
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
    Point rotleft() const {
		return Point(-y,x);
	}
};

struct Line{
	Point s,e;
    double angle;
	Line(){}
	bool operator ==(Line v){
		return (s == v.s)&&(e == v.e);
	}
    void calcangle(){
		angle = atan2(e.y-s.y,e.x-s.x);
	}
	bool operator <(const Line &b)const{
		return angle < b.angle;
	}
    Line(Point _s, Point _e) {
        s = _s; e = _e;
    }
	//ax+by+c=0
	Line(double a,double b,double c){
		if(sgn(a) == 0){
			s = Point(0,-c/b);
			e = Point(1,-c/b);
		}
		else if(sgn(b) == 0){
			s = Point(-c/a,0);
			e = Point(-c/a,1);
		}
		else{
			s = Point(0,-c/b);
			e = Point(1,(-c-a)/b);
		}
        Point tmp = s + (e-s).rotleft();
        if(sgn(a*tmp.x+b*tmp.y+c) > 0) swap(s, e);
	}
	//`两向量平行(对应直线平行或重合)`
	bool parallel(Line v){
		return sgn((e-s)^(v.e-v.s)) == 0;
	}
	//`求两直线的交点`
	//`要保证两直线不平行或重合`
	Point crosspoint(Line v){
		double a1 = (v.e-v.s)^(s-v.s);
		double a2 = (v.e-v.s)^(e-v.s);
		return Point((s.x*a2-e.x*a1)/(a2-a1),(s.y*a2-e.y*a1)/(a2-a1));
	}
};

struct polygon{
	int n;
	Point p[N];
	void input(int _n){
		n = _n;
		for(int i = 0;i < n;i++)
			p[i].input();
	}
	void add(Point q){
		p[n++] = q;
	}
    double getarea(){
		double sum = 0;
		for(int i = 0;i < n;i++){
			sum += (p[i]^p[(i+1)%n]);
		}
		return fabs(sum)/2;
	}
};

struct halfplanes{
	int n;
	Line hp[N];
	Point p[N];
	int que[N];
	int st,ed;
	void push(Line tmp){
		hp[n++] = tmp;
	}
	//去重
	void unique(){
		int m = 1;
		for(int i = 1;i < n;i++){
			if(sgn(hp[i].angle-hp[i-1].angle) != 0)
				hp[m++] = hp[i];
			else if(sgn( (hp[m-1].e-hp[m-1].s)^(hp[i].s-hp[m-1].s) ) > 0)
				hp[m-1] = hp[i];
		}
		n = m;
	}
	bool halfplaneinsert(){
		for(int i = 0;i < n;i++)hp[i].calcangle();
		sort(hp,hp+n);
		unique();
		que[st=0] = 0;
		que[ed=1] = 1;
		p[1] = hp[0].crosspoint(hp[1]);
		for(int i = 2;i < n;i++){
			while(st<ed && sgn((hp[i].e-hp[i].s)^(p[ed]-hp[i].s))<0)ed--;
			while(st<ed && sgn((hp[i].e-hp[i].s)^(p[st+1]-hp[i].s))<0)st++;
			que[++ed] = i;
			if(hp[i].parallel(hp[que[ed-1]]))return false;
			p[ed]=hp[i].crosspoint(hp[que[ed-1]]);
		}
		while(st<ed && sgn((hp[que[st]].e-hp[que[st]].s)^(p[ed]-hp[que[st]].s))<0)ed--;
		while(st<ed && sgn((hp[que[ed]].e-hp[que[ed]].s)^(p[st+1]-hp[que[ed]].s))<0)st++;
		if(st+1>=ed)return false;
		return true;
	}
	//`得到最后半平面交得到的凸多边形`
	//`需要先调用halfplaneinsert() 且返回true`
	void getconvex(polygon &con){
		p[st] = hp[que[st]].crosspoint(hp[que[ed]]);
		con.n = ed-st+1;
		for(int j = st,i = 0;j <= ed;i++,j++)
			con.p[i] = p[j];
	}
};

polygon con, po;
halfplanes hps;
Point p[N];
int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        p[i].input();
        po.add(p[i]);
    }
    p[n] = p[0];
    for(int i = 0; i < n; ++i) {
        hps.push(Line(p[i], p[i+1]));
    }
    Point a, b, c, d;
    for(int i = 1; i < n; ++i) {
        a = p[0]; b = p[1]; c = p[i]; d = p[i+1];
        hps.push(Line(a.y-b.y-c.y+d.y, -a.x+b.x+c.x-d.x, a.x*b.y-a.y*b.x-c.x*d.y+c.y*d.x));
    }
    double S, A;
    if(hps.halfplaneinsert()) {
        hps.getconvex(con);
        S = con.getarea();
    } else {
        S = 0.0;
    }
    A = po.getarea();
    printf("%.4f\n", S / A);
}
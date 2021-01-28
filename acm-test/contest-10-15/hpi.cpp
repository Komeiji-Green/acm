#include<bits/stdc++.h>
#include<cmath>
using namespace std;
const double eps = 1e-9;
const double pi = acos(-1.0);
const int maxp = 1010;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
inline double sqr(double x) { return x * x; }

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) { x = _x, y = _y; }
    void input() {scanf("%lf%lf", &x, &y);}
    bool operator == (Point b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    Point operator-(const Point& b) const {
        return Point(x - b.x, y - b.y);
    }
    Point operator+(const Point& b) const {
        return Point(x + b.x, y + b.y);
    }
    double operator*(const Point& b) const {
        return x * b.x + y * b.y;
    }
    double operator^(const Point& b) const {
        return x * b.y - y * b.x;
    }
    Point rotleft() {
        return Point(-y, x);
    }
    double len() {
        return hypot(x, y);
    }
    Point trunc(double r){
        double l = len();
        if(!sgn(l)) return *this;
        r /= l;
        return Point(x * r, y * r);
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
	}
	void input(){
		s.input();
		e.input();
	}
	//`返回直线倾斜角 0<=angle<pi`
	double angle(){
		double k = atan2(e.y-s.y,e.x-s.x);
		if(sgn(k) < 0)k += pi;
		if(sgn(k-pi) == 0)k -= pi;
		return k;
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
	// 点在线段上的判断
	bool pointonseg(Point p){
		return sgn((p-s)^(e-s)) == 0 && sgn((p-s)*(p-e)) <= 0;
	}
	//`两向量平行(对应直线平行或重合)`
	bool parallel(Line v){
		return sgn((e-s)^(v.e-v.s)) == 0;
	}
	//`两线段相交判断`
	//`2 规范相交`
	//`1 非规范相交`
	//`0 不相交`
	int segcrossseg(Line v){
		int d1 = sgn((e-s)^(v.s-s));
		int d2 = sgn((e-s)^(v.e-s));
		int d3 = sgn((v.e-v.s)^(s-v.s));
		int d4 = sgn((v.e-v.s)^(e-v.s));
		if( (d1^d2)==-2 && (d3^d4)==-2 )return 2;
		return (d1==0 && sgn((v.s-s)*(v.s-e))<=0) ||
			(d2==0 && sgn((v.e-s)*(v.e-e))<=0) ||
			(d3==0 && sgn((s-v.s)*(s-v.e))<=0) ||
			(d4==0 && sgn((e-v.s)*(e-v.e))<=0);
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
	//`两直线关系`
	//`0 平行`
	//`1 重合`
	//`2 相交`
	int linecrossline(Line v){
		if((*this).parallel(v))
			return v.relation(s)==3;
		return 2;
	}
	//`求两直线的交点`
	//`要保证两直线不平行或重合`
	Point crosspoint(Line v){
		double a1 = (v.e-v.s)^(s-v.s);
		double a2 = (v.e-v.s)^(e-v.s);
		return Point((s.x*a2-e.x*a1)/(a2-a1),(s.y*a2-e.y*a1)/(a2-a1));
	}
};

struct polygon {
    int n;
    Point p[maxp];
    Line l[maxp];
    void add(Point q) {
        p[n++] = q;
    }
    void input(int _n) {
        n = _n;
        for(int i = 0; i < n; ++i)
            p[i].input();
    }
    void getline() {
        for(int i = 0; i < n; ++i) {
            l[i] = Line(p[i], p[(i + 1) % n]);
        }
    }
    double getarea() {
        double sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += (p[i] ^ p[(i + 1) % n]);
        }
        return fabs(sum) / 2;
    }
    double getcircu() {
        double sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += (p[(i + 1) % n] - p[i]).len();
        }
        return sum;
    }
};

struct halfplane:public Line{
	double angle;
	halfplane(){}
	//`表示向量s->e逆时针(左侧)的半平面`
	halfplane(Point _s,Point _e){
		s = _s;
		e = _e;
	}
	halfplane(Line v){
		s = v.s;
		e = v.e;
	}
	void calcangle(){
		angle = atan2(e.y-s.y,e.x-s.x);
	}
	bool operator <(const halfplane &b)const{
		return angle < b.angle;
	}
};

struct halfplanes{
	int n;
	halfplane hp[maxp];
	Point p[maxp];
	int que[maxp];
	int st,ed;
	void push(halfplane tmp){
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

polygon po[20], con;
halfplanes hps;

int main() {
    int n, m;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &m);
        po[i].input(m);
    }

    hps.n = 0;
    for(int i = 1; i <= n; ++i) {
        po[i].getline();
        for(int j = 0; j < po[i].n; ++j) {
            hps.push(halfplane(po[i].l[j]));
        }
    }
    if(hps.halfplaneinsert()) {
        hps.getconvex(con);
        printf("%.3f\n", con.getarea());
    } else {
        printf("%.3f\n", 0.0);
    }
}
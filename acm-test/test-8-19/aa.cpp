#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;


const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxn = 233333;
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


struct polygon{
	int n;
	Point p[maxn];
	void input(int _n){
		n = _n;
		for(int i = 0;i < n;i++)
			p[i].input();
	}
	void add(Point q){
		p[n++] = q;
	}
	
	//`得到面积`
	double getarea(){
		double sum = 0;
		for(int i = 0;i < n;i++){
			sum += (p[i]^p[(i+1)%n]);
		}
		return fabs(sum)/2;
	}
};


struct Line {
    Point s, e;
    Line() {}
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
        // <= 0
        Point temp = s + (e - s).rotleft();
        if(sgn(a * temp.x + b * temp.y + c) > 0) {
            swap(s, e);
        }
	}
    Line(Point _s, Point _e) {
        s = _s;
        e = _e;
    }
    double getAngle() const {
        return atan2(e.y - s.y, e.x - s.x);
    }
};


struct cmp {
    bool operator() (const Line& a, const Line& b) {
        int d = sgn(a.getAngle() - b.getAngle());
        if(d == 0) {
            return ((a.e - a.s) ^ (b.e - a.s)) >= 0;
        }
        return d < 0;
    }
};


Point crosspoint(Line u, Line v) {
	double a1 = (v.e-v.s)^(u.s-v.s);
	double a2 = (v.e-v.s)^(u.e-v.s);
	return Point((u.s.x*a2-u.e.x*a1)/(a2-a1),(u.s.y*a2-u.e.y*a1)/(a2-a1));
}

//判断 b,c 的交点是否在 a 的右边
bool onRight(Line a, Line b, Line c)
{
    Point o = crosspoint(b, c);
    if (((a.e - a.s) ^ (o - a.s)) < 0)
        return true;
    return false;
}


Line L[maxn];
Line que[maxn];
Point p[maxn];  // 交点
int n;

void HalfPlaneIntersection(polygon& con)
{
    sort(L, L + n, cmp());             //排序
    int head = 0, tail = 0, cnt = 0; //双端队列
    //去重。
    for (int i = 0; i < n - 1; i++)
    {
        if (sgn(L[i].getAngle() - L[i + 1].getAngle()) == 0)
        {
            continue;
        }
        L[cnt++] = L[i];
    }
    L[cnt++] = L[n - 1];

    for (int i = 0; i < cnt; i++)
    {
        //判断新加入直线产生的影响
        while (tail - head > 1 && onRight(L[i], que[tail - 1], que[tail - 2]))
            tail--;
        while (tail - head > 1 && onRight(L[i], que[head], que[head + 1]))
            head++;
        que[tail++] = L[i];
    }
    //最后判断最先加入的直线和最后的直线的影响
    while (tail - head > 1 && onRight(que[head], que[tail - 1], que[tail - 2]))
        tail--;
    while (tail - head > 1 && onRight(que[tail - 1], que[head], que[head + 1]))
        head++;
    
    con.add(crosspoint(que[head], que[tail - 1]));
    for(int i = 1, j = head + 1; j < tail; i++, j++) {
        con.add( crosspoint(que[j], que[j - 1]) );
    }
}


int main()
{
    int num;
    cin >> num;
    polygon play;
    play.input(num);

    n = 0;
    for(int i = 0; i < num; i++) {
        L[n++] = Line(play.p[i % num], play.p[(i + 1) % num]);
    }
    Point a, b, c, d;
    a = play.p[0];
    b = play.p[1];
    for(int i = 1; i < num; i++) {
        c = play.p[i % num], d = play.p[(i + 1) % num];
        L[n++] = Line(
            -(b.y - a.y - d.y + c.y),
            b.x - a.x - d.x + c.x,
            -b.x * a.y + b.y * a.x + d.x * c.y - d.y * c.x
        );
    }

    polygon con;
    HalfPlaneIntersection(con);
    double P = con.getarea() / play.getarea();
    printf("%.4f\n", P);
}





#include<bits/stdc++.h>

using namespace std;

// `计算几何模板`
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 100050;
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	else return x < 0 ? -1 : 1;
}
//square of a double
inline double sqr(double x){return x*x;}
struct Point{
	double x,y, rad;
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
		return sgn(rad - b.rad) == 0;
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
    void getrad() {
        rad = atan2(y, x);
    }
};
struct Line{
	Point s,e;
	Line(){}
	Line(Point _s,Point _e){
		s = _s;
		e = _e;
	}

	// 点在线段上的判断
	bool pointonseg(Point p){
		return sgn((p-s)^(e-s)) == 0 && sgn((p-s)*(p-e)) <= 0;
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
    double length() {
        return s.distance(e);
    }
};

Point p[maxp], v[maxp], cen;
int tag[maxp], n;
Line e[4];

int main() {
    int T;
    cin >> T;
    int cas = 0;
    double w, h, ans;
    while(T--) {
        ++cas;
        scanf("%lf%lf", &w, &h);
        e[0] = Line(Point(0, 0), Point(w, 0));
        e[1] = Line(Point(w, 0), Point(w, h));
        e[2] = Line(Point(w, h), Point(0, h));
        e[3] = Line(Point(0, h), Point(0, 0));
        cen.input();
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) {
            p[i].input();
        }
        for(int i = 0; i < n; ++i) {
            p[i] = p[i] - cen;
            p[i].getrad();
        }
        sort(p, p + n);
        n = unique(p, p + n) - p;
        if(n == 1) {
            ans = 2 * w + 2 * h;
            printf("Case #%d: %.8f\n", cas, ans);
            continue;
        }

        ans = 0.0;

        //printf("1!!!!\n");
        Point pp; Line ll;
        for(int i = 0; i < n; ++i) {
            ll = Line(cen, p[i] + cen);
            for(int j = 0; j < 4; ++j) {
                if(e[j].parallel(ll)) continue;
                pp = e[j].crosspoint(ll);
                if(sgn((pp - ll.s) * (ll.e - ll.s)) >= 0 && e[j].pointonseg(pp)) {
                    v[i] = pp; tag[i] = j;
                    break;
                }
            }
        }

        //printf("2!!!!\n");

        /*for(int i = 0; i < n; ++i) {
            v[i].output();
            printf("%d\n", tag[i]);
        }*/

        double len;
        for(int i = 0, j, tg; i < n; ++i) {
            j = (i + 1) % n;
            tg = tag[i];
            if(tag[i] == tag[j] && sgn((v[j] - v[i]) * (e[tg].e - v[i])) >= 0) {
                ans = max(ans, v[i].distance(v[j]));
            } else {
                len = 0;
                len += v[i].distance(e[tag[i]].e);
                len += v[j].distance(e[tag[j]].s);
                for(tg = (tg + 1) % 4; tg != tag[j]; tg = (tg + 1) % 4) {
                    len += e[tg].length();
                }
                ans = max(ans, len);
            }
        }

        printf("Case #%d: %.8f\n", cas, ans);
    }
}
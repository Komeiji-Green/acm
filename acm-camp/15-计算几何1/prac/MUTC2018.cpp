#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

// `计算几何模板`
const double eps = 1e-2;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 1010;
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
    double length(){
		return s.distance(e);
	}
    bool pointonseg(Point p){
		return sgn((p-s)^(e-s)) == 0 && sgn((p-s)*(p-e)) <= 0;
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
    double dispointtoline(Point p){
		return fabs((p-s)^(e-s))/length();
	}
    double dispointtoseg(Point p){
		if(sgn((p-s)*(e-s))<0 || sgn((p-e)*(s-e))<0)
			return min(p.distance(s),p.distance(e));
		return dispointtoline(p);
	}
    //`返回点p在直线上的投影`
	Point lineprog(Point p){
		Point v = e - s;
		return s + ( (v * (v*(p-s))) / (v.len2()) );
	}
};

struct circle{
	Point p;//圆心
	double r;//半径
	circle(){}
	circle(Point _p,double _r){
		p = _p;
		r = _r;
	}
	circle(double x,double y,double _r){
		p = Point(x,y);
		r = _r;
	}
	//输入
	void input(){
		p.input();
		scanf("%lf",&r);
	}
	//输出
	void output(){
		printf("%.2lf %.2lf %.2lf\n",p.x,p.y,r);
	}
	//`点和圆的关系`
	//`0 圆外`
	//`1 圆上`
	//`2 圆内`
	int relation(Point b){
		double dst = b.distance(p);
		if(sgn(dst-r) < 0)return 2;
		else if(sgn(dst-r)==0)return 1;
		return 0;
	}
	//`线段和圆的关系`
	//`比较的是圆心到线段的距离和半径的关系`
	int relationseg(Line v){
		double dst = v.dispointtoseg(p);
		if(sgn(dst-r) < 0)return 2;
		else if(sgn(dst-r) == 0)return 1;
		return 0;
	}
	//`直线和圆的关系`
	//`比较的是圆心到直线的距离和半径的关系`
	int relationline(Line v){
		double dst = v.dispointtoline(p);
		if(sgn(dst-r) < 0)return 2;
		else if(sgn(dst-r) == 0)return 1;
		return 0;
	}
	//`两圆的关系`
	//`5 相离`
	//`4 外切`
	//`3 相交`
	//`2 内切`
	//`1 内含`
	//`需要Point的distance`
	//`测试：UVA12304`
	int relationcircle(circle v){
		double d = p.distance(v.p);
		if(sgn(d-r-v.r) > 0)return 5;
		if(sgn(d-r-v.r) == 0)return 4;
		double l = fabs(r-v.r);
		if(sgn(d-r-v.r)<0 && sgn(d-l)>0)return 3;
		if(sgn(d-l)==0)return 2;
		if(sgn(d-l)<0)return 1;
	}
	//`求两个圆的交点，返回0表示没有交点，返回1是一个交点，2是两个交点`
	//`需要relationcircle`
	//`测试：UVA12304`
	int pointcrosscircle(circle v,Point &p1,Point &p2){
		int rel = relationcircle(v);
		if(rel == 1 || rel == 5) return 0;
		double d = p.distance(v.p);
		double l = (d*d+r*r-v.r*v.r)/(2*d);
		double h = sqrt(r*r-l*l);
		Point tmp = p + (v.p-p).trunc(l);
		p1 = tmp + ((v.p-p).rotleft().trunc(h));
		p2 = tmp + ((v.p-p).rotright().trunc(h));
		if(rel == 2 || rel == 4)
			return 1;
		return 2;
	}
	//`求直线和圆的交点，返回交点个数`
	int pointcrossline(Line v,Point &p1,Point &p2){
		if(!(*this).relationline(v))return 0;
		Point a = v.lineprog(p);
		double d = v.dispointtoline(p);
		d = sqrt(r*r-d*d);
		if(sgn(d) == 0){
			p1 = a;
			p2 = a;
			return 1;
		}
		p1 = a + (v.e-v.s).trunc(d);
		p2 = a - (v.e-v.s).trunc(d);
		return 2;
	}
};

double R;
struct polygon{
	int n, tot;
	Point p[maxp];
	Line l[maxp];
    Point li[maxp*maxp]; // 所有交点

    circle cir[maxp];
    Line line[maxp];

    void getpoint() {
        Point s, e, v, tmp[2];
        int cnt;
        for(int i = 0; i < n; ++i) {
            v = p[(i+1)%n]-p[i];
            s = p[i]+v.trunc(R).rotleft();
            e = s + v;
            line[i] = Line(s, e);
        }
        for(int i = 0; i < n; ++i) {
            cir[i] = circle(p[i], R);
        }
        tot = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                if(!line[i].parallel(line[j])) {
                    li[tot++] = line[i].crosspoint(line[j]);
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                cnt = cir[i].pointcrossline(line[j], tmp[0], tmp[1]);
                for(int k = 0; k < cnt; ++k) li[tot++] = tmp[k];
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                cnt = cir[i].pointcrosscircle(cir[j], tmp[0], tmp[1]);
                for(int k = 0; k < cnt; ++k) li[tot++] = tmp[k];
            }
        }
        int num = 0;
        for(int i = 0; i < tot; ++i) {
            if(relationcircle(circle(li[i], R))) {
                li[num++] = li[i];
            }
        }
        tot = num;
    }
    double chk(Point o) {
        Point tmp[2];
        int num = tot, cnt;
        li[num++] = o;
        for(int i = 0; i < n; ++i) {
            li[num++] = line[i].lineprog(o);
        }
        for(int i = 0; i < n; ++i) {
            if(o == cir[i].p) continue;
            cnt = cir[i].pointcrossline(Line(o, cir[i].p), tmp[0], tmp[1]);
            for(int j = 0; j < cnt; ++j) li[num++] = tmp[j];
        }
        cnt = num; num = tot;
        for(int i = tot; i < cnt; ++i) {
            if(relationcircle(circle(li[i], R))) li[num++] = li[i];
        }
        double res = inf;
        for(int i = 0; i < num; ++i) {
            res = min(res, o.distance(li[i]));
        }
        return res;
    }
	void input(int _n){
		n = _n;
		for(int i = 0;i < n;i++)
			p[i].input();
	}
	void add(Point q){
		p[n++] = q;
	}
	void getline(){
		for(int i = 0;i < n;i++){
			l[i] = Line(p[i],p[(i+1)%n]);
		}
	}
	//`判断点和任意多边形的关系`
	//` 3 点上`
	//` 2 边上`
	//` 1 内部`
	//` 0 外部`
	int relationpoint(Point q){
		for(int i = 0;i < n;i++){
			if(p[i] == q)return 3;
		}
		for(int i = 0;i < n;i++){
			if(l[i].pointonseg(q))return 2;
		}
		int cnt = 0;
		for(int i = 0;i < n;i++){
			int j = (i+1)%n;
			int k = sgn((q-p[j])^(p[i]-p[j]));
			int u = sgn(p[i].y-q.y);
			int v = sgn(p[j].y-q.y);
			if(k > 0 && u < 0 && v >= 0)cnt++;
			if(k < 0 && v < 0 && u >= 0)cnt--;
		}
		return cnt != 0;
	}
	//`多边形和圆关系`
	//` 2 圆完全在多边形内`
	//` 1 圆在多边形里面，碰到了多边形边界`
	//` 0 其它`
	int relationcircle(circle c){
		int x = 2;
		if(relationpoint(c.p) != 1)return 0;//圆心不在内部
		for(int i = 0;i < n;i++){
			if(c.relationseg(l[i])==2)return 0;
			if(c.relationseg(l[i])==1)x = 1;
		}
		return x;
	}
};


Point st[maxp];
polygon po;
int main() {
    int T, n, m;
    cin >> T;
    bool f = 1;
    double res;
    ll ans;
    while(T--) {
        cin >> n >> m;
        scanf("%lf", &R);
        po.input(n); po.getline(); po.getpoint();
        for(int i = 0; i < m; ++i) st[i].input();
        for(int i = 0; i < m; ++i) {
            res = po.chk(st[i]);
            ans = (ll)(res + 0.5);
            printf("%lld\n", ans);
        }
    }
}

/*
for(int i = 0; i < n && f; ++i) {
    for(int j = i + 1; j < n && f; ++j) {
        if(p[i] == p[j]) f = 0;
    }
}
for(int i = 0; i < n && f; ++i) {
    Point x = p[i==0?n-1:i-1], y = p[i+1];
    if(Line(x, p[i]).relation(y) == 3) f = 0;
}*/
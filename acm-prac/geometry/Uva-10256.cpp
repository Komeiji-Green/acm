#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

typedef long long ll;

const int maxp = 5010;
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
		scanf("%lld%lld",&x,&y);
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
	bool pointonseg(Point p){
		return sgn((p-s)^(e-s)) == 0 && sgn((p-s)*(p-e)) <= 0;
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
	
};

struct polygon{
	int n;
	Point p[maxp];
    Line l[maxp];
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
    void getline(){
		for(int i = 0;i < n;i++){
			l[i] = Line(p[i],p[(i+1)%n]);
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
    //`判断点和任意多边形的关系`
	//` 3 点上`
	//` 2 边上`
	//` 1 内部`
	//` 0 外部`
	int relationpoint(Point q){
		for(int i = 0;i < n;i++){
			if(p[i] == q)return 3;
		}
		getline();
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
};

int main() {
    int n, m;
    polygon A, B, cona, conb;
    while(scanf("%d%d", &n, &m) != EOF && n && m) {
        A.input(n);
        B.input(m);
        A.getconvex(cona);
        B.getconvex(conb);
        cona.getline();
        conb.getline();
        n = cona.n;
        m = conb.n;
        bool flag = true;
        for(int i = 0; i < n; ++i) {
            if(conb.relationpoint(cona.p[i])) {
                flag = false;
                break;
            }
        }
        if(!flag) {
            printf("No\n");
            continue;
        }
        for(int j = 0; j < m; ++j) {
            if(cona.relationpoint(conb.p[j])) {
                flag = false;
                break;
            }
        }
        if(!flag) {
            printf("No\n");
            continue;
        }
        for(int i = 0; i < n && flag; ++i) {
            for(int j = 0; j < m && flag; ++j) {
                if(cona.l[i].segcrossseg(conb.l[j])) {
                    flag = false;
                }
            }
        }
        if(!flag) {
            printf("No\n");
            continue;
        }
        printf("Yes\n");
    }
}
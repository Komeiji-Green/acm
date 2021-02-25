#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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
    int quad()const {
        return (x > 0 || x == 0 && y > 0) ? 0 : 1;
    }
};

struct polygon{
	int n;
	Point p[N];
	void input(int _n){
		n = _n;
		for(int i = 0; i < n;i++)
			p[i].input();
	}
	void add(Point q){
		p[n++] = q;
	}
    void rev() {
        for(int i = 0; i < n; ++i) p[i] = Point(-p[i].x,-p[i].y);
    }
    int getedge(Point* li) {
        p[n] = p[0];
        for(int i = 0; i < n; ++i) li[i] = p[i+1] - p[i];
        return n;
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
    Point minv() {
        Point mi = p[0];
        for(int i = 1; i < n; ++i) mi = min(mi, p[i]);
        return mi;
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
		convex.norm();//`原来得到的是顺时针的点，排序后逆时针`
	}
};

bool cmp(const Point& a, const Point& b) {
    int qa = a.quad(), qb = b.quad();
    if(qa != qb) return qa < qb;
    return sgn(a ^ b) > 0;
}

Point a[N], b[N], p[N];
polygon po1, po2, con1, con2;
int main() {
    int n, m, q;
    cin >> n >> m >> q;
    po1.input(n); po2.input(m); po2.rev();
    po1.getconvex(con1); po2.getconvex(con2);
    Point o1 = con1.minv(), o2 = con2.minv();
    Point o = o1 + o2;
    int len1 = con1.getedge(a), len2 = con2.getedge(b);
    int len = len1 + len2;
    for(int i = len1; i < len; ++i) a[i] = b[i-len1];
    sort(a, a + len, cmp);
    p[0] = o;
    int r = 0, rr = 0;
    for(int i = 1; i <= len; ++i) {
        p[i] = p[i-1] + a[i-1];
        if(sgn(p[i].x-p[r].x)>0) r = i;
		if(sgn(p[i].x-p[rr].x)>=0) rr = i;
    }

	//printf("pol\n");
	//for(int i = 0; i <= len; ++i) p[i].output();
    Point c;
    while(q--) {
        c.input();
        double lx = p[0].x, rx = p[r].x;
        if(sgn(c.x-lx)<0 || sgn(c.x-rx)>0) printf("0\n");
        else {
            bool in = 1;
            int le = 0, ri = r;
            int mid = ((le + ri + 1) >> 1);
            while(le < ri) {
                if(sgn(p[mid].x-c.x)>=0) {
                    ri = mid - 1;
                } else {
                    le = mid;
                }
                mid = ((le + ri + 1) >> 1);
            }
            if(sgn(c.y-p[mid].y)<0&&sgn(c.y-p[mid+1].y)<0||sgn((p[mid+1]-c)^(p[mid]-c)) > 0) in = 0;
            le = rr; ri = len;
            mid = ((le + ri + 1) >> 1);
            while(le < ri) {
                if(sgn(p[mid].x-c.x)<=0) {
                    ri = mid - 1;
                } else {
                    le = mid;
                }
                mid = ((le + ri + 1) >> 1);
            }
            if(sgn(c.y-p[mid].y)>0&&sgn(c.y-p[mid+1].y)>0||sgn((p[mid+1]-c)^(p[mid]-c)) > 0) in = 0;
            if(in) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
    }
}
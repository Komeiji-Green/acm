#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// `计算几何模板`
const double eps = 1e-15;
const double inf = 1e20;
const double pi = acos(-1.0);
const int N = 2333333;
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
    void output() {
        for(int i = 0; i < n; ++i) p[i].output();
    }
	void add(Point q){
		p[n++] = q;
	}
    int getedge(Point* li) {
        p[n] = p[0];
        for(int i = 0; i < n; ++i) li[i] = p[i+1] - p[i];
        return n;
    }
	// 上凸包
    void getconvex(polygon &con) {
        sort(p, p + n);
        con.n = n;
        for(int i = 0; i < min(n, 2); ++i) con.p[i] = p[i];
        if(con.n == 2 && con.p[0] == con.p[1]) con.n--;
        if(n <= 2) return;
        int &top = con.n;
        top = 1;
        for(int i = 2; i < n; ++i) {
            while(top && sgn((con.p[top]-p[i])^(con.p[top-1]-p[i])) <= 0) --top;
            con.p[++top] = p[i];
        }
        ++top;
    }
};

polygon po, con;
Point p[N];
double d[N];
int main() {
    int n;
    cin >> n;
    po.input(n);
    po.getconvex(con);

    //con.output();
    for(int i = 0; i < con.n; ++i) p[i] = con.p[i];
    n = con.n;
    int h = 0;
    for(int i = 1; i < n; ++i) {
        if(sgn(p[i].y-p[h].y) >= 0) h = i;
    }
    double ans = inf, k, cur;
    for(int i = h; i + 1 < n; ++i) {
        d[i] = (p[i+1].x - p[i].x) / (p[i].y - p[i+1].y);
        k = d[i];
        cur = (1 + 1/k) * p[i].x + (1 + k) * p[i].y;
        ans = min(ans, cur);
    }
    for(int i = h; i < n; ++i) {
        k = sqrt(p[i].x / p[i].y);
        if(i > h && sgn(k-d[i-1]) > 0 || i + 1 < n && sgn(k-d[i]) < 0) continue;
        cur = (1 + 1/k) * p[i].x + (1 + k) * p[i].y;
        ans = min(ans, cur);
    }
    printf("%.4f\n", ans);
}
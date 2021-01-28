#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 4005;
const int N = 1145;

struct Edge {
    int from, to, pre;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b) {
    tot++;
    e[tot].from = a; e[tot].to = b;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b) { ine(a, b); ine(b, a); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)



const double eps = 1e-10;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 1010;

int sgn(double x){
	if(fabs(x) < eps)return 0;
	else return x < 0 ? -1 : 1;
}

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
		printf("%.7f %.7f\n",x,y);
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

vector<int> nxt[N];
int n;

int dfn[N], clc = 0;
void change(int x, int dad) {
    dfn[x] = clc++;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        nxt[x].push_back(y);
        change(y, x);
    }
}

double theta[N];
Point vec[N], p[N];
void dfs(int x, double ang) {
    int deg = nxt[x].size();
    if(deg == 0) return;
    double aa = ang / deg;
    for(int i = 0; i < deg; ++i) {
        theta[nxt[x][i]] = theta[x] + aa * i;
        vec[nxt[x][i]] = vec[1].rotate(Point(0, 0), theta[nxt[x][i]]);
        dfs(nxt[x][i], aa);
    }
}

void getans(int x) {
    int deg = nxt[x].size();
    for(int i = 0; i < deg; ++i) {
        p[nxt[x][i]] = p[x] + vec[nxt[x][i]];
        getans(nxt[x][i]);
    }
}


int main() {
    cin >> n;
    int u, v;
    for(int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        ine2(u, v);
    }
    change(1, 0);
    vec[1] = Point(1, 0);
    double the = pi / (n - 1);
    for(int i = 1; i <= n; ++i) {
        vec[i] = Point(1, 0).rotate(Point(0, 0), the * dfn[i]);
    }
    p[1] = Point(0, 0);
    getans(1);

    for(int i = 1; i <= n; ++i) {
        p[i].output();
    }
}
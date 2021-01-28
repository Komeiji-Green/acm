
#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;


const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 5005;
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
    int l, id;  // 长度及所属线段
    int tp;     // 左右端点

	Point(){}
    Point(double _x,double _y){
		x = _x;
		y = _y;
	}
	Point(double _x,double _y,int _l,int _id,int _tp){
		x = _x;
		y = _y;
        l = _l;
        id = _id;
        tp = _tp;
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
};

struct polygon{
    polygon(): n(0) {}
	int n;
	Point p[maxp];
    Point tmp[maxp];
    int diff[maxp]; // 差分
    bool vis[maxp]; // 遇到的线段

	void input(int _n){
		n = _n;
		for(int i = 0;i < n;i++)
			p[i].input();
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
				return a.tp > b.tp;
			}
			return d > 0;
		}
	};
	//`进行极角排序`
	void norm(){
		Point mi = p[0];
		for(int i = 1;i < n;i++)mi = min(mi,p[i]);
		sort(p,p+n,cmp(mi));
	}

    int gao() {
        memcpy(tmp, p, sizeof(p));
        int ans = 0;
        int num = n;
        for(int i = 0; i < num; i++) {
            Point cur = tmp[i];
            double x = cur.x;
            double y = cur.y;
            n = 0;
            for(int j = 0; j < num; j++) {
                int c = sgn(tmp[j].y - y);
                if(c == 0) continue;
                Point nex = Point(tmp[j]);
                if(c == -1) {
                    nex.y = y + y - nex.y;
                    nex.x = x + x - nex.x;
                    nex.tp ^= 1;
                }
                add(nex);
            }
            sort(p, p + n, cmp(cur));

            memset(diff, 0, sizeof(diff));
            memset(vis, 0, sizeof(vis));
            for(int i = 0; i < n; i++) {
                int id = p[i].id, w = p[i].l;
                if(vis[id]) {
                    diff[i] = -w;
                } else {
                    diff[i] = w;
                    vis[id] = true;
                }
            }
            int maxv = cur.l;
            int sum = cur.l;
            for(int i = 0; i < n; i++) {
                sum += diff[i];
                maxv = max(maxv, sum);
            }
            ans = max(ans, maxv);
        }
        return ans;
    }
};



int main() 
{
    int n;
    cin >> n;
    int x0, x1, y;
    polygon pol;
    for(int i = 1; i <= n; i++) {
        scanf("%d %d %d", &x0, &x1, &y);
        if(x0 > x1) swap(x0, x1);
        pol.add(Point(x0, y, abs(x0 - x1), i, 0));
        pol.add(Point(x1, y, abs(x0 - x1), i, 1));
    }
    printf("%d\n", pol.gao());
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// `计算几何模板`
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 5050;
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	else return x < 0 ? -1 : 1;
}
int sgn(ll x) {
    if(!x) return 0;
    else return x < 0 ? -1 : 1;
}
//square of a double
inline double sqr(double x){return x*x;}


struct Point{
	ll x, y; int rad, id;
	Point(){}
	Point(ll _x,ll _y){
		x = _x;
		y = _y;
	}
	void input(){
		scanf("%lld%lld",&x,&y);
	}
	void output(){
		printf("%lld %lld\n",x,y);
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
	//返回两点的距离
	ll distance(Point p){
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
    void getrad(const Point& c) {
        rad = ( sgn(y-c.y) > 0 || sgn(y-c.y) == 0 && sgn(x-c.x) > 0 ) ? 0 : 1;
    }
};

struct cmp {
    Point c;
    cmp(Point _c): c(_c) {}
    bool operator() (const Point& a, const Point& b) {
        return a.rad < b.rad || a.rad == b.rad && ( sgn((a - c) ^ (b - c)) > 0 );
    }
};

Point inp[maxp], p[maxp];
int vis[maxp], cnt[3];
double expp[maxp];
int main() {
    int n, nn;
    int tot = 0;
    cin >> n;
    expp[0] = 1.0;
    for(int i = 1; i <= n; ++i) {
        expp[i] = 0.5 * expp[i - 1];
    }
    for(int i = 0; i < n; ++i) {
        inp[tot].input(); inp[tot++].id = i;
        inp[tot].input(); inp[tot++].id = i;
    }
    nn = n;
    n = tot;
    Point c;
    double ans = 0.0, cur;
    for(int x = 0; x < n; ++x) {
        memcpy(p, inp, sizeof(inp));
        if(x) swap(p[x], p[0]);
        c = p[0];
        for(int i = 1; i < n; ++i) {
            p[i].getrad(c);
        }
        cmp cp(c);
        sort(p + 1, p + n, cp);
        int m = 2 * n - 1;
        for(int i = 1; i < n; ++i) {
            p[i + n - 1] = p[i];
            p[i + n - 1].rad += 2;
        }
        Point rt;
        cnt[0] = nn; cnt[1] = 0; cnt[2] = 0;
        memset(vis, 0, sizeof(vis));
        --cnt[vis[p[1].id]];
        ++vis[p[1].id];
        ++cnt[vis[p[1].id]];
        for(int i = 1, j = 1; i < n; ++i) {
            rt = c - (p[i] - c);
            rt.rad = p[i].rad + 1;
            while((j + 1 < m) && cp(p[j + 1], rt)) {
                ++j;
                --cnt[vis[p[j].id]];
                ++vis[p[j].id];
                ++cnt[vis[p[j].id]];
            }
            --cnt[vis[p[i].id]];
            --vis[p[i].id];
            ++cnt[vis[p[i].id]];
            if(c.id == p[i].id) continue;
            /*
            cur = (c ^ p[i]) * 0.125;
            for(int k = 0; k < nn; ++k) {
                if(k == c.id || k == p[i].id) continue;
                if(!vis[k]) {
                    cur = 0; break;
                }
                if(vis[k] == 1) cur *= 0.5;
            }
            ans += cur;
            */
            
            --cnt[vis[c.id]];
            --cnt[vis[p[i].id]];
            if(!cnt[0]) {
                ans += (c ^ p[i]) * 0.125 * expp[cnt[1]];
            }
            ++cnt[vis[c.id]]; 
            ++cnt[vis[p[i].id]];
            
        }
    }
    printf("%.10f\n", ans);
}
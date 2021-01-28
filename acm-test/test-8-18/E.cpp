#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
const int mod = 998244353;


// 快速幂 计算 a^k % p
// a <= 1e9, k <= 1e9
int Pow(int a, int k, int p) 
{
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

int inv3;


const int maxp = 5005;
//`Compares a ll to zero`
int sgn(ll x){
	if(x == 0)return 0;
	if(x < 0)return -1;
	else return 1;
}
//square of a ll
inline ll sqr(ll x){return x*x;}



struct Point{
	ll x,y;

	Point(){}
    Point(ll _x,ll _y){
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
	ll operator ^(const Point &b)const{
		return x*b.y - y*b.x;
	}
	//点积
	ll operator *(const Point &b)const{
		return x*b.x + y*b.y;
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
    Point operator %(const ll &k)const {
        return Point(x % k, y % k);
    }
    //`逆时针旋转90度`
	Point rotleft(){
		return Point(-y,x);
	}
    Point rotleft(const Point &c) {
        Point pp = *this - c;
        return c + pp.rotleft();
    }
};

int Area(Point a, Point b, Point c) {
    return ((b - a) ^ (c - b)) % 998244353;
}

struct polygon{
    polygon(): n(0) {}
	int n;
	Point p[maxp];
    Point tmp[maxp];
    Point pre[maxp];

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
			Point pa = aa - p, pb = bb - p;
            int ya = sgn(pa.y), yb = sgn(pb.y);
			if(ya == 0 && yb == 0) {
                return pa.x > pb.x;
            } else if(ya >= 0 && yb < 0) {
                return true;
            } else if(ya < 0 && yb >= 0) {
                return false;
            }
            ll d = sgn(pa ^ pb);
			return d > 0;
		}
	};

    struct cmp2 {
        Point p;
        cmp2(const Point&p0) {p = p0;}
        int operator()(const Point &aa, const Point&bb) {
            return -sgn((aa - p) ^ (bb - p));
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
            n = 0;
            for(int j = 0; j < num; j++) {
                if(j == i) continue;
                add(tmp[j]);
            }
            sort(p, p + n, cmp(cur));
            for(int i = 0; i < n; i++) {
                p[i + n] = p[i];
            }

            printf("(%d, %d): ", cur.x, cur.y);
            for(int i = 0; i < n; i++) {
                printf("(%d, %d) ", p[i].x, p[i].y);
            }
            printf("\n");

            pre[0] = Point(0, 0);
            for(int i = 1; i <= 2 * n; i++) {
                pre[i] = (pre[i - 1] + p[i - 1] - cur) % mod;
            }

            cmp2 cp(cur);
            Point sum1(0, 0), sum2(0, 0);
            // sum1 : [p0 ~ p1)   sum2 : [p1 ~ p2)
            for(int j = 0, p0 = 0, p1 = 0, p2 = 0; j < n; j++) {
                Point pt = p[j];
                Point pl = pt.rotleft(cur);
                Point pll = pl.rotleft(cur);

                //printf("(%d, %d) ", pl.x, pl.y);

                /*int st;
                while((p0 % n) != j) {
                    sum1 = (sum1 - (p[p0 % n] - cur)) % mod;
                    //sum1 = (sum1 - (p[p0 % n] - cur));
                    p0++;
                }
                st = p0;
                while(p0 < st + n && cp(pt, p[p0 % n]) == 0 && cp(p[p0 % n], pl) < 0) {
                    sum1 = (sum1 - (p[p0 % n] - cur)) % mod;
                    //sum1 = (sum1 - (p[p0 % n] - cur));
                    p0++;
                }*/

                int st;

                if(p1 < j) p1 = j;
                st = p1;
                while(p1 < st + n && cp(pt, p[p1 % n]) <= 0 && cp(p[p1 % n], pl) < 0) {
                    p1++;
                }
                if(p2 < p1) p2 = p1;
                st = p2;
                while(p2 < st + n && cp(pl, p[p2 % n]) <= 0 && cp(p[p2 % n], pll) < 0)
                    p2++;
                /*while(p1 < p0 || (p1 < p0 + n && cp(pt, p[p1 % n]) < 0 && cp(p[p1 % n], pl) < 0)) {
                    sum1 = (sum1 + (p[p1 % n] - cur)) % mod;
                    //sum1 = (sum1 + (p[p1 % n] - cur));
                    sum2 = (sum2 - (p[p1 % n] - cur)) % mod;
                    //sum2 = (sum2 - (p[p1 % n] - cur));
                    p1++;
                }
                while(p2 < p1 || (p2 < p1 + n && cp(pl, p[p2 % n]) <= 0 && cp(p[p2 % n], pll) < 0)) {
                    sum2 = (sum2 + (p[p2 % n] - cur)) % mod;
                    //sum2 = (sum2 + (p[p2 % n] - pt));
                    p2++;
                }*/

                //ans = (1ll * ans + (sum1 ^ (pt - cur))) % mod;
                ans = (1ll * ans + ((pt - cur) ^ (pre[p1] - pre[j]))) % mod;
                printf("%d ", ans);
                //ans = (1ll * ans - 2 * (sum2 ^ (pt - cur))) % mod;
                ans = (1ll * ans - 2 * ((pt - cur) ^ (pre[p2] - pre[p1]))) % mod;
                printf("%d \n", ans);
                
                printf("%d: %d %d %d\n", j, p0, p1, p2);
            }
        }
        return ans;
    }
};


int main()
{
    inv3 = Pow(3, mod - 2, mod);

    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        long long x, y;
        polygon pol;
        for(int i = 0; i < n; i++) {
            scanf("%lld %lld", &x, &y);
            pol.add(Point(x, y));
        }
        int ans = 1ll * pol.gao() * inv3 % mod;
        if(ans < 0) ans += mod;
        printf("%d\n", ans);
    }
}

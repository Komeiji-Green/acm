#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>


using namespace std;
typedef __int128 ll;
const ll mod = 998244353;
const long double pi = acos((long double)-1.0);
const long double hpi = asin((long double)1.0);
const long double eps = 1e-8;
// 被卡了精度，我死了


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
int sgn(long double x){
	if(fabs(x) < eps)return 0;
	if(x < 0)return -1;
	else return 1;
}
//square of a ll
inline ll sqr(ll x){return x*x;}



struct Point{
	ll x,y;
    int rd;

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
	/*bool operator < (Point b)const{
		return sgn(reg - b.reg) < 0;
	}*/
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
        Point ret = Point(-y, x);
        ret.rd = rd;
        if(ret.y >= 0 && y < 0) ret.rd++;
		return ret;
	}
    /*long double getAngle()const {
        return atan2((long double)(y), (long double)(x));
    }*/
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
    // 以p为中心进行极角排序
	struct cmp{
		bool operator()(const Point &aa,const Point &bb) {
            if(aa.rd != bb.rd) {
                return aa.rd < bb.rd;
            }
            if(aa.y == 0 && bb.y == 0) {
                if(aa.x > 0 && bb.x < 0) return true;
                else if(aa.x < 0 && bb.x > 0) return false;
            } else if (aa.y >= 0 && bb.y < 0) {
                return true;
            } else if (aa.y < 0 && bb.y >= 0) {
                return false;
            }
            return (aa ^ bb) > 0;
		}
	};

    ll gao() {
        memcpy(tmp, p, sizeof(p));
        ll ans = 0;
        int num = n;
        for(int i = 0; i < num; i++) {
            Point cur = tmp[i];
            n = 0;
            for(int j = 0; j < num; j++) {
                if(i == j) continue;
                Point pp = tmp[j] - cur;
                pp.rd = 0;
                //pp.reg = pp.getAngle();
                add(pp);
            }
            sort(p, p + n, cmp());

            //printf("22\n");
    
            for(int j = 0; j < n; j++) {
                p[j + n] = p[j];
                p[j + n].rd = 1;
            }

            /*printf("(%lld, %lld)::\n", cur.x, cur.y);
            for(int j = 0; j < 2 * n; j++) {
                printf("(%lld, %lld): %Lf\n", p[j].x, p[j].y, p[j].reg);
            }*/

            pre[0] = Point(0, 0);
            for(int j = 1; j <= 2 * n; j++) {
                pre[j] = (pre[j - 1] + p[j - 1]) % mod;
            }

            //printf("33\n");

            for(int j = 0, p1 = 0, p2 = 0; j < n; j++) {
                Point pt = p[j];
                Point ple = pt.rotleft();
                Point plele = ple.rotleft();

                //printf("ple: (%lld, %lld): %Lf\n", ple.x, ple.y, ple.reg);
                //printf("plele: (%lld, %lld): %Lf\n", plele.x, plele.y, plele.reg);
                cmp cp;
                while(p1 < 2 * n && cp(p[p1], ple)) p1++;
                while(p2 < 2 * n && cp(p[p2], plele)) p2++;

                //printf("%d: %d %d\n", j, p1, p2);
                
                ans += (pt ^ (pre[p1] - pre[j])) % mod;
                ans %= mod;
                ans -= (pt ^ (pre[p2] - pre[p1])) % mod * 2ll % mod;
                ans = (ans + mod) % mod;
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

    //long double test = (long double)1000000000000000000;
    //printf("%Lf %f\n", atan2(test, test), atan2(1, 1));
    while(T--) {
        int n;
        cin >> n;
        long long x, y;
        polygon pol;
        for(int i = 0; i < n; i++) {
            scanf("%lld %lld", &x, &y);
            pol.add(Point(x, y));
        }
        ll ret = pol.gao();
        ret = ret * inv3 % mod;
        long long ans = ret;
        if(ans < 0) ans += mod;
        printf("%lld\n", ans);
        //printf("%d\n", 1ll * ((100000000000000000 % mod) * (100000000000000000 % mod)) % mod * 10 % mod);
    }
}
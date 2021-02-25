#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
const lll mod = 998244353;

// `计算几何模板`
const double eps = 1e-15;
const double inf = 1e20;
const double pi = acos(-1.0);
const int N = 5050;
//`Compares a double to zero`
int sgn(lll x){
    if(x == 0) return 0;
    else return x < 0 ? -1 : 1;
}
//square of a double
inline double sqr(double x){return x*x;}

struct Point{
    lll x, y; int quad;
	Point(){}
	Point(lll _x, lll _y){
		x = _x;
		y = _y;
	}
	void input(){
        ll _x, _y;
		scanf("%lld%lld",&_x,&_y);
        x = _x; y = _y;
	}
	void output(){
        ll _x = x, _y = y;
		printf("%lld %lld\n",_x,_y);
	}
	bool operator == (Point b)const{
		return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;
	}
	bool operator < (Point b)const{
		if(quad != b.quad) return quad < b.quad;
        else return sgn((*this)^b) > 0;
	}
	Point operator +(const Point &b)const{
		return Point(x+b.x,y+b.y);
	}
	Point operator -(const Point &b)const{
		return Point(x-b.x,y-b.y);
	}
    Point operator %(const ll p) const {
        return Point(x % p, y % p);
    }
    Point operator *(const lll p) const {
        return Point(x * p, y * p);
    }
	//叉积
	lll operator ^(const Point &b)const{
		return x*b.y - y*b.x;
	}
	//点积
	lll operator *(const Point &b)const{
		return x*b.x + y*b.y;
	}
    Point rotleft() const {
        Point res = Point(-y,x);
        res.calcquad();
        if(res.quad % 2 != quad % 2) res.quad = quad + 1;
        else res.quad = quad;
		return res;
	}
    int getquad() {
        return (x > 0 || x == 0 && y > 0) ? 0 : 1;
    }
    void calcquad() {
        quad = (x > 0 || x == 0 && y > 0) ? 0 : 1;
    }
};

Point p[N], q[N], pre[N];

int main() {
    //printf("%lld\n", Pow(3ll ,mod-2, mod));
    int T, n, m;
    Point c, sum1, sum2, r1, r2;
    lll ans = 0;
    cin >> T;
    while(T--) {
        ans = 0;
        cin >> n;
        m = 2 * n;
        for(int i = 0; i < n; ++i) p[i].input();
        for(int i = 0; i < n; ++i) {
            c = p[i];
            int tot = 0;
            for(int j = 0; j < n; ++j) {
                if(j == i) continue;
                q[tot++] = p[j] - p[i];
            }
            m = 2 * tot;
            for(int j = 0; j < tot; ++j) {
                q[j+tot] = q[j];
                q[j].calcquad(); q[j+tot].quad = q[j].quad + 2;
            }
            sort(q, q + m);

            pre[0] = Point(0, 0);
            for(int j = 0; j < m; ++j) {
                pre[j+1] = (pre[j] + q[j]) % mod;
            }

            for(int j = 0, k = 0, l = 0; j < tot; ++j) {
                r1 = q[j].rotleft();
                r2 = r1.rotleft();
                while(k+1==j || k+1<m && q[k+1]<r1) ++k;
                while(l+1==j || l+1<m && q[l+1]<r2) ++l;
                sum1 = pre[k+1] * 3 - pre[l+1] * 2 - pre[j+1];
                ans = (ans + (q[j] ^ sum1) % mod) % mod;
            }
        }
        ll res = ans;
        res = res * 332748118ll % 998244353;
        printf("%lld\n", (res + 998244353) % 998244353);
    }
}

#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;

// `计算几何模板`
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 8080;
//`Compares a double to zero`
inline int sgn(ll x) {
    if(x == 0) return 0;
    if(x > 0) return 1;
    else return -1; 
}
//square of a double
inline double sqr(double x){return x*x;}

struct Point{
	ll x,y;
    int rd, id;

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
	bool operator == (const Point &b)const{
        return x == b.x && y == b.y;
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

int cnt[maxp];

inline bool eq(const Point& a, const Point& b) {
    return a.rd == b.rd && (a ^ b) == 0 && (a * b) >= 0;
}

struct polygon{
    polygon(): n(0) {}
	int n, o, q;
	Point p[maxp];
    Point tmp[maxp];
    Point pre[maxp];
	void input(int _o, int _q){
		n = _o + _q;
        o = _o, q = _q;
		for(int i = 0; i < n; i++)
			tmp[i].input();
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
                return aa.x > 0 && bb.x < 0;
            } else if (aa.y >= 0 && bb.y < 0) {
                return true;
            } else if (aa.y < 0 && bb.y >= 0) {
                return false;
            }
            return (aa ^ bb) > 0;
		}
	};

    void gao() {
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; ++i) {
            Point cur = tmp[i];
            int last = 0;
            for(int j = 0; j < n; ++j) {
                if(tmp[j] == cur) continue;
                p[last] = tmp[j] - cur;
                p[last].rd = 0;
                p[last].id = j;
                ++last;
            }
            cmp cp;
            sort(p, p + last, cp);
            //p[last].num = 1;

            for(int j = 0; j < last; ++j) {
                int jj = last + j;
                p[jj] = p[j];
                p[jj].rd = 1;
            }
        
            int m = 2 * last;

            int j1, j2, k1, k2;
            j1 = j2 = k1 = k2 = 0;

            int cj1, cj2, ck1, ck2;
            while(j2 < last) {
                j1 = j2;
                cj1 = cj2 = 0;
                while(j2 < m && eq(p[j1], p[j2])) {
                    p[j2].id >= o ? ++cj1 : ++cj2;
                    ++j2;
                }
                Point rt = p[j1].rotleft();
                while(k1 < m && cp(p[k1], rt)) ++k1;
                k2 = k1;
                if(k1 < m && (p[k1] ^ rt) == 0 && (p[k1] * rt) >= 0) {
                    ck1 = ck2 = 0;
                    while(k2 < m && eq(p[k1], p[k2])) {
                        p[k2].id >= o ? ++ck1 : ++ck2;
                        ++k2;
                    }
                    int mm = 0;
                    if(i >= o) ++mm;
                    cnt[i] += mm == 0 ? cj1 * ck2 + cj2 * ck1 : cj2 * ck2;
                    
                    if(mm == 1) {
                        for(int k = j1, id; k < j2; ++k) if((id = p[k].id) < o) cnt[id] += ck2;
                        for(int k = k1, id; k < k2; ++k) if((id = p[k].id) < o) cnt[id] += cj2;
                    } else {
                        for(int k = j1, id; k < j2; ++k) {
                            id = p[k].id;
                            cnt[id] += ((id >= o) ? ck2 : ck1);
                        }
                        for(int k = k1, id; k < k2; ++k) {
                            id = p[k].id;
                            cnt[id] += ((id >= o) ? cj2 : cj1);
                        }
                    }
                }

            }

            /*for(int j = 0, k = 0; j < last; ++j) {
                Point rt = p[j].rotleft();
                while(k < m && cp(p[k], rt)) ++k;
                if(k < m && (p[k] ^ rt) == 0 && (p[k] * rt) >= 0) {
                    int cj1 = 0, cj2 = 0;
                    for(auto uid : list[j])
                        uid >= o ? ++cj1 : ++cj2;
        
                    int ck1 = 0, ck2 = 0;
                    for(auto vid : list[k])
                        vid >= o ? ++ck1 : ++ ck2;
        
                    int mm = 0;
                    if(i >= o) ++mm;
                    cnt[i] += mm == 0 ? cj1 * ck2 + cj2 * ck1 : cj2 * ck2;

                    if(mm == 1) {
                        for(auto id : list[j]) if(id < o) cnt[id] += ck2;
                        for(auto id : list[k]) if(id < o) cnt[id] += cj2;
                    } else {
                        for(auto id : list[j]) cnt[id] += ((id >= o) ? ck2 : ck1);
                        for(auto id : list[k]) cnt[id] += ((id >= o) ? cj2 : cj1);
                    }
                }
            }*/
        }
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    polygon po;
    po.input(n, q);
    po.gao();
    for(int i = n; i < n + q; i++) {
        printf("%d\n", cnt[i]);
    }
}
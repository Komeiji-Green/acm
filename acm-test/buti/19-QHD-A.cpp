#pragma optimize("Ofast")
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

struct polygon{
    polygon(): n(0) {}
	int n, o, q;
	Point p[maxp];
    Point tmp[maxp];
    Point pre[maxp];
    vector<int> list[maxp];

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

    void gao() {
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; i++) {
            Point cur = tmp[i];
            int tot = 0;
            for(int j = 0; j < n; j++) {
                if(tmp[j] == cur) continue;
                p[tot] = tmp[j] - cur;
                p[tot].rd = 0;
                p[tot].id = j;
                tot++;
            }
            cmp cp;
            sort(p, p + tot, cp);
            int last = 0;
            //p[last].num = 1;

            vector<int> emp;
            list[last].swap(emp);
            list[last].push_back(p[0].id);

            for(int j = 1; j < tot; j++) {
                if((p[j] ^ p[last]) == 0) {
                    //p[last].num++;
                    list[last].push_back(p[j].id);
                } else {
                    ++last;
                    p[last] = p[j];
                    //p[last].num = 1;

                    vector<int> ep;
                    list[last].swap(ep);
                    list[last].push_back(p[j].id);
                }
            }
            last++;
            for(int j = 0; j < last; j++) {
                int jj = last + j;
                p[jj] = p[j];
                p[jj].rd = 1;
                vector<int> ep;
                list[jj].swap(ep);
                for(int k = 0; k < list[j].size(); k++) {
                    list[jj].push_back(list[j][k]);
                }
            }
        
            int m = 2 * last;

            for(int j = 0, k = 0; j < last; j++) {
                Point rt = p[j].rotleft();
                while(k < m && cp(p[k], rt)) k++;
                if(k < m && ((p[k] ^ rt) == 0 && (p[k] * rt) >= 0)) {
                    int cj1 = 0, cj2 = 0;
                    for(auto uid : list[j]) {
                        if(uid >= o) cj1++;
                        else cj2++;
                    }
                    int ck1 = 0, ck2 = 0;
                    for(auto vid : list[k]) {
                        if(vid >= o) ck1++;
                        else ck2++;
                    }
                    int mm = 0;
                    if(i >= o) mm++;
                    if(mm == 0) {
                        cnt[i] += cj1 * ck2 + cj2 * ck1;
                    } else {
                        cnt[i] += cj2 * ck2;
                    }
                    if(mm == 1) {
                        for(auto id : list[j]) if(id < o) cnt[id] += ck2;
                        for(auto id : list[k]) if(id < o) cnt[id] += cj2;
                    } else {
                        for(auto id : list[j]) cnt[id] += ((id >= o) ? ck2 : ck1);
                        for(auto id : list[k]) cnt[id] += ((id >= o) ? cj2 : cj1);
                    }
                    /*for(auto uid : list[j]) {
                        for(auto vid : list[k]) {
                            int mm = 0;
                            if(uid >= o) mm++;
                            if(vid >= o) mm++;
                            if(i >= o) mm++;
                            if(mm == 1) {
                                cnt[uid]++;
                                cnt[vid]++;
                                cnt[i]++;
                                //printf("%d %d %d\n", uid, vid, i);
                            }
                        }
                    }*/
                    /*int nums = p[k].num;
                    for(auto id : list[j]) {
                        cnt[id] += nums;
                    }
                    nums = p[j].num;
                    for(auto id : list[k]) {
                        cnt[id] += nums;
                    }
                    cnt[i] += p[k].num * p[j].num;*/
                    ///k++;
                }
            }
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
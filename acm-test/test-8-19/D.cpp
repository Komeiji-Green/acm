#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;

const double eps = 1e-8;

const int maxp = 110;
//`Compares a int to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	if(x < 0)return -1;
	else return 1;
}
int sgn(int x) {
    if(x == 0) return 0;
    if(x < 0) return -1;
    else return 1;
}
//square of a int
inline int sqr(int x){return x*x;}


struct Point{
	int x, y;
    int id;
	Point(){}
	Point(int _x,int _y){
		x = _x;
		y = _y;
	}
	void input(){
		scanf("%d%d",&x,&y);
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
	int operator ^(const Point &b)const{
		return x*b.y - y*b.x;
	}
	//点积
	int operator *(const Point &b)const{
		return x*b.x + y*b.y;
	}
	//返回长度
	double len(){
		return hypot(x,y);//库函数
	}
	//返回长度的平方
	int len2(){
		return x*x + y*y;
	}
	//返回两点的距离
	int distance(Point p){
		return hypot(x-p.x,y-p.y);
	}
	Point operator +(const Point &b)const{
		return Point(x+b.x,y+b.y);
	}
	Point operator *(const int &k)const{
		return Point(x*k,y*k);
	}
	Point operator /(const int &k)const{
		return Point(x/k,y/k);
	}
	//`计算pa  和  pb 的夹角`
	//`就是求这个点看a,b 所成的夹角`
	//`测试 LightOJ1203`
	int rad(Point a,Point b){
		Point p = *this;
		return fabs(atan2( fabs((a-p)^(b-p)),(a-p)*(b-p) ));
	}
	//`化为长度为r的向量`
	Point trunc(int r){
		int l = len();
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
	Point rotate(Point p,int angle){
		Point v = (*this) - p;
		int c = cos(angle), s = sin(angle);
		return Point(p.x + v.x*c - v.y*s,p.y + v.x*s + v.y*c);
	}
};

struct cmp {
    Point p;
    cmp(const Point &p0) { p = p0; }
    bool operator() (const Point& aa, const Point& bb) {
        Point a = aa - p, b = bb - p;
        int d = sgn(a ^ b);
        if(d == 0) {
            return sgn(a.len2() - b.len2()) > 0;
        } else {
            return d > 0;
        }
    }  
};

struct cmp2 {
    Point p;
    cmp2(const Point &p0) { p = p0; }
    bool operator() (const Point& aa, const Point& bb) {
        return sgn((aa - p) ^ (bb - p)) > 0;
    }
};

int dp[maxp][maxp];  // 枚举：类似于凸包生成算法中的当前边
Point tmp[maxp];
Point p[maxp];
Point pp[maxp];
int mm[maxp];

int gao(int st, int n) {
    Point cent = tmp[st];
    int num = 0;
    for(int i = st + 1; i <= n; i++) {
        p[++num] = tmp[i];
    }

    //printf("%d: (%d, %d)\n", st, cent.x, cent.y);
    sort(p + 1, p + num + 1, cmp(cent));
    /*for(int i = 1; i <= num; i++) {
        printf("%d:(%d, %d)  ", i, p[i].x, p[i].y);
    }
    printf("\n");*/

    memset(dp, 0, sizeof(dp));

    int ans = 0;
    
    for(int i = 1; i <= num; i++) {
        Point cur = p[i];
        cmp2 cp(cur);
        for(int j = 1; j <= num; j++) {
            pp[j] = p[j];
            pp[j].id = j;
        }
        sort(pp + 1, pp + i, cmp(cur));
        sort(pp + i + 1, pp + num + 1, cmp(cur));
        mm[0] = 0;
        for(int j = 1; j < i; j++) {
            mm[j] = max(mm[j - 1], dp[pp[j].id][i]);
        }
        Point pre = pp[num];
        
        bool flag = false;
        for(int j = num, k = i - 1; j > i; j--) {
            if(sgn((cur - cent) ^ (pp[j] - cent)) == 0) {
                pre = pp[j - 1];
                flag = true;
                continue;
            }
            if(sgn((pre - cent) ^ (pp[j] - cent)) <= 0) {
                pre = pp[j];
                Point dir = pp[j] - cur;
                while(k > 0 && (dir ^ (pp[k] - cur)) < 0) k--;
                dp[i][pp[j].id] = (flag ? 0 : mm[k]) + ((cur - cent) ^ (pp[j] - cent));
                ans = max(ans, dp[i][pp[j].id]);
            }
        }
    }

    /*printf("ans: %d\n", ans);
    for(int i = 1; i <= num; i++) {
        for(int j = i + 1; j <= num; j++) {
            printf("(%d %d: %d) ", i, j, dp[i][j]);
        }
        printf("\n");
    }*/

    return ans;
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        int x, y;
        for(int i = 1; i <= n; i++) {
            scanf("%d %d", &x, &y);
            tmp[i] = Point(x, y);
        }
        sort(tmp + 1, tmp + n + 1);
        
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            int tp = gao(i, n);
            //printf("%d: %d\n", i, tp);
            ans = max(ans, tp);
        }
        printf("%.1f\n", (double)ans / 2.0);
    }
}
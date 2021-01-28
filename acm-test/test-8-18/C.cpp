#include<iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;

const int N = 1005;

//`Compares a int to zero`
int sgn(int x){
	if(x == 0) return 0;
	if(x < 0)return -1;
	else return 1;
}


struct Point{
	int x,y;
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
	Point operator +(const Point &b)const{
		return Point(x+b.x,y+b.y);
	}
	Point operator *(const int &k)const{
		return Point(x*k,y*k);
	}
	Point operator /(const int &k)const{
		return Point(x/k,y/k);
	}
};


struct Line{
	Point s,e;
	Line(){}
	Line(Point _s,Point _e){
		s = _s;
		e = _e;
	}

	void input(){
		s.input();
		e.input();
	}
	void adjust(){
		if(e < s)swap(s,e);
	}

    // -------- e
    //
    // -------- s
    bool lower(Point p) {
        return ((e - s) ^ (p - s)) < 0;
    }
};

struct cmp {
    bool operator() (const Line& lhs, const Line& rhs) {
        return lhs.s.x < rhs.s.x;
    }
};

Line a[N];
int cnt[N];
int ans[N];

int main()
{
    int n, m, x1, y1, x2, y2;
    while(scanf("%d", &n) != EOF && n != 0) {
        scanf("%d%d%d%d%d", &m, &x1, &y1, &x2, &y2);

        int u, l;
        a[0] = Line(Point(x1, y2), Point(x1, y1));
        for(int i = 1; i <= n; i++) {
            scanf("%d %d", &u, &l);
            a[i] = Line(Point(l, y2), Point(u, y1));
        }

        sort(a, a + n + 1, cmp());

        memset(cnt, 0, sizeof(cnt));
        memset(ans, 0, sizeof(ans));
        Point p;
        for(int i = 0; i < m; i++) {
            p.input();
            int le = 0, ri = n;
            int mid = (le + ri + 1) >> 1;
            while(le < ri) {
                if(a[mid].lower(p)) {
                    le = mid;
                } else {
                    ri = mid - 1;
                }
                mid = (le + ri + 1) >> 1;
            }
            cnt[mid]++;
        }
        for(int i = 0; i <= n; i++) {
            ans[cnt[i]]++;
        }

        printf("Box\n");
        for(int i = 1; i <= m; i++) {
            if(ans[i]) {
                printf("%d: %d\n", i, ans[i]);
            }
        }
    }
}
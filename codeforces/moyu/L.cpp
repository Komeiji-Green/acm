#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const double eps = 1e-9;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 5050;
int sgn(ll x) {
	if(x == 0) return 0;
	else return x < 0 ? -1 : 1;
}
struct Point {
	ll x, y; int cnt;
	Point() {
	}
	Point(ll _x, ll _y) {
		x = _x; y = _y;
	}
	void input() {
		scanf("%lld%lld", &x, &y);
		cnt = 1;
	}
	void output() {
		printf("%lld %lld\n", x, y);
	}
	bool operator==(Point b) const {
		return sgn(x - b.x)==0 && sgn(y - b.y)==0;
	}
	bool operator<(Point b) const {
		return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
	}
	Point operator-(const Point& b) const {
		return Point(x - b.x, y - b.y);
	}
	double operator^(const Point& b) const {
		return x * b.y - y * b.x;
	}
	double operator*(const Point& b) const {
		return x * b.x + y * b.y;
	}
	Point operator+(const Point& b) const {
		return Point(x + b.x, y + b.y);
	}
	double distance(Point p) {
		return hypot(x - p.x, y - p.y);
	}
};

Point tmp[maxp];
Point rd[maxp];

struct polygon {
	int n;
	Point p[maxp];
	void input(int _n) {
		n = _n;
		for(int i = 0; i < n; ++i) p[i].input();
	}
	void add(Point q) {
		p[n++] = q;
	}
	void extend() {
		for(int i = 0; i < n; ++i) tmp[i] = p[i];
		int tot = 0;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < tmp[i].cnt; ++j)
				p[tot++] = tmp[i];
		}
		n = tot;
	}
	struct cmp {
		Point p;
		cmp(const Point& p0) {
			p = p0;
		}
		bool operator()(const Point& aa, const Point& bb) {
			Point a = aa, b = bb;
			int d = sgn((a - p)^(b - p));
			if(d == 0) {
				return sgn(a.distance(p)-b.distance(p)) < 0;
			}
			return d > 0;
		}
	};
	void norm() {
		Point mi = p[0];
		for(int i = 1; i < n; ++i) mi = min(mi, p[i]);
		sort(p, p + n, cmp(mi));
	}
	
	void getconvex(polygon& con) {
		for(int i = 0; i < n; ++i) rd[i] = p[i];
		sort(p, p + n);
		int tot = 0;
		for(int i = 1; i < n; ++i) {
			if(p[i] == p[tot]) {
				p[tot].cnt++; //printf("!!\n");
			} else {
				p[++tot] = p[i];
			}
		}
		++tot;
		n = tot;
		//printf("n: %d\n", n);
		con.n = n;
		for(int i = 0; i < min(n, 2); ++i) {
			con.p[i] = p[i];
		}
		if(con.n == 2 && (con.p[0] == con.p[1])) con.n--;
		if(n <= 2) return;
		int& top = con.n;
		top = 1;
		for(int i = 2; i < n; ++i) {
			while(top && sgn((con.p[top]-p[i])^(con.p[top-1]-p[i])) <= 0) top--;
			con.p[++top] = p[i];
		}
		int tmp = top;
		con.p[++top] = p[n-2];
		for(int i = n - 3; i >= 0; --i) {
			while(top != tmp && sgn((con.p[top]-p[i])^(con.p[top-1]-p[i])) <= 0) top--;
			con.p[++top] = p[i];
		}
		if(con.n == 2 && (con.p[0] == con.p[1])) con.n--;
		con.norm();
	}               
};

ll calc(Point a, Point b, Point c) {
	return abs((c - a) ^ (b - a));
}

int main() {
	int T;
	cin>>T;
	polygon po, con;
	Point cen;
	ll ans, cur, tri, uu;
	while(T--) {
		int n, m;
		scanf("%d", &n);
		po.input(n);
		po.getconvex(con);
		con.extend();
		//for(int i = 0; i < con.n; ++i) {
			//printf("ttt: "); con.p[i].output();
		//}
		m = n;
		n = con.n;
		ans = 0;
		Point *p = con.p;
		if(n <= 2) {
			printf("0\n"); continue;
		}
		if(n == 3) {
			ans = 0;
			tri = calc(p[0], p[1], p[2]);
			for(int i = 0; i < m; ++i) {
				if(rd[i] == p[0] || rd[i] == p[1] || rd[i] == p[2]) continue;
				uu = calc(p[0], p[1], rd[i]);
				uu = min(uu, min(calc(p[0], p[2], rd[i]), calc(p[1], p[2], rd[i])));
				cur = tri - uu;
				ans = max(ans, cur);
			}
		} else {
		for(int i = 0; i < n; ++i) {
			for(int j = (i+2)%n, r = (i+1)%n, s = (i+3)%n; j != i; j = (j + 1)%n) {
				while((r+1)%n != j && sgn((p[(r+1)%n]-p[r])^(p[j]-p[i])) > 0) r = (r+1)%n;
				while((s+1)%n != i && sgn((p[j]-p[i])^(p[(s+1)%n]-p[s])) > 0) s = (s+1)%n;
				cur = ((p[r]-p[i])^(p[j]-p[i]))+((p[s]-p[j])^(p[i]-p[j]));
				ans = max(cur, ans);
			}
		}
		}
		if(ans%2==0) {
			printf("%lld\n", ans / 2);
		} else {
			printf("%lld.5\n", ans / 2);
		}
	}	
}


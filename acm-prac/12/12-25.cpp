#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5020;
const int inf = 0x3f3f3f3f;
int n;
int sgn(ll x) {
	if(x == 0) return 0;
	else return x < 0 ? -1 : 1;
}
struct Point {
	ll x, y;
	Point() {
	}
	Point(ll _x, ll _y) {
		x = _x; y = _y;
	}
	void input() {
		scanf("%lld%lld", &x, &y);
	}
	Point operator-(const Point& b) const {
		return Point(x - b.x, y - b.y);
	}
	Point operator+(const Point& b) const {
		return Point(x + b.x, y + b.y);
	}
	double operator*(const Point& b) const {
		return x*b.x+y*b.y;
	}
	double operator^(const Point& b) const {
		return x*b.y-y*b.x;
	}
};
Point p[maxn], q[maxn];
struct I {
	int le, ri, id;
	bool operator< (const I& b) {
		return le < b.le;
	}
} uu[maxn];
int bd[maxn], id[maxn];
int o[maxn][maxn];
int main() {
	int T, m, sz;
	cin >> T;
	Point v;
	int ans, cur, pos, tot;
	while(T--) {
		tot = 0;
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; ++i) p[i].input();
		for(int i = 0; i < n; ++i) p[n+i]=p[i];
		p[2*n] = p[0]; sz = 2 * n;
		for(int j = 0; j < m; ++j) q[j].input();
		for(int j = 0, i, c1, c2; j < m; ++j) {
			v = q[j];
			i = 1;
			++tot;
			for(int i = 1; i <= n; ++i) {
				c1 = sgn( (p[i]-p[i-1])^(p[i]-v) );
				c2 = sgn( (p[i+1]-p[i])^(p[i]-v) );
				if(c1 == -1 && c2 == 1) uu[tot].le = i;
				if(c1 == 1 && c2 == -1) uu[tot].ri = i - 1;
			}
			if(uu[tot].ri < uu[tot].le) uu[tot].ri += n;
			uu[tot].id = j + 1;
			printf("itv:  le: %d, ri: %d, id: %d\n", uu[tot].le, uu[tot].ri, uu[tot].id);
			++tot;
			uu[tot].le = uu[tot-1].le+n;
			uu[tot].ri = uu[tot-1].ri+n;
			uu[tot].id = j + 1;

			
			/*while(i < sz && (sgn( (p[i]-p[i-1])^(p[i]-v) ) != -1 ||  sgn( (p[i+1]-p[i])^(p[i]-v) ) != 1)) ++i;
			++tot;
			uu[tot].le = i;
			while(i < sz && (sgn( (p[i]-p[i-1])^(p[i]-v) ) != 1 ||  sgn( (p[i+1]-p[i])^(p[i]-v) ) != -1)) ++i;
			uu[tot].ri = i - 1;
			uu[tot].id = j + 1;
			++tot;
			uu[tot].le = uu[tot-1].le+n;
			uu[tot].ri = uu[tot-1].ri+n;
			uu[tot].id = j + 1;*/
		}
		
		/* 
		for(int i = 0; i <= sz; ++i) bd[i] = 0, id[i] = 0;
		for(int i = 1; i <= tot; ++i) {
			//printf("itv:  le: %d, ri: %d, id: %d\n", uu[i].le, uu[i].ri, uu[i].id);
			if(uu[i].ri > bd[uu[i].le]) bd[uu[i].le] = uu[i].ri, id[uu[i].le] = uu[i].id;
		}
		bd[0] = 0;
		for(int i = 1; i <= sz; ++i) {
			if(bd[i-1] > bd[i]) bd[i] = bd[i-1], id[i] = id[i-1];
		} 
		ans = inf;
		for(int i = 1, j, la; i <= n; ++i) {
			la = i + n; cur = 0; j = i;
			if(uu[id[j]].le != i) continue;
			while(j < la) {
				if(bd[j] < j) {
					cur = 0; break;
				} else {
					++cur; j = bd[j] + 1;
				}
			}
			if(cur && cur < ans) ans = cur, pos = i;	
		}
		if(ans < inf) {
			printf("%d\n", ans);
			for(int j = pos, la = pos + n; j < la; j = bd[j] + 1) {
				printf("%d ", id[j]);
			}
			printf("\n");
		} else printf("-1\n");
		
		*/ 
	
		ans = inf; 
		sort(uu + 1, uu + tot + 1);
		for(int i = 1, now, rt, t, j, maxv; i <= tot; ++i) {
			if(uu[i].le > n) break;
			t = uu[i].le + n - 1;
			now = i; j = i + 1;
			cur = 1; o[i][cur] = uu[i].id;
			while(uu[now].ri < t) {
				rt = uu[now].ri + 1; maxv = rt - 1;
				now = 0;
				for(;j <= tot && uu[j].le <= rt; ++j) {
					if(uu[j].ri > maxv) {
						maxv = uu[j].ri;
						now = j;
					}
				}
				if(!now) {
					cur = 0; break;
				} else {
					++cur; o[i][cur] = uu[now].id;
				}
			}
			if(cur && cur < ans) ans = cur, pos = i;
		}
		if(ans == inf) {
			printf("-1\n");
		} else {
			printf("%d\n", ans);
			for(int i = 1; i <= ans; ++i) {
				printf("%d ", o[pos][i]);
			}
			printf("\n");
		}
		/*
		for(int i = 1, s, t, lb, now; i <= tot; ++i) {
			s = uu[i].le; t = s + n - 1;
			if(s > n) break;
			lb = uu[i].ri; now = i;
			cur = 1;
			for(int j = i + 1; j <= tot; ++j) {
				if(lb >= t) break;
				if(uu[j].le <= lb) {
					
				} else if(uu[j].le > lb) {
					if(uu[j].le > uu[now].ri) break;
					else 
				}
			}
			for(int j = i + 1, now = i; j <= tot; ++j) {
				if(rb >= t) {
					if(cur < ans) pos = i, ans = cur;
					break;
				}
				if(uu[j].le > lb && uu[j].le > rb) break;
				if(uu[j].le > lb) lb = rb, ++cur;
				if(uu[j].ri > rb) now = i, rb = uu[j].ri;
			}
		}
		if(!ans) ans = -1;
		printf("%d\n", ans);
		if(ans) {
			int t = uu[pos].le + n - 1, lb = uu[pos].le, rb = uu[pos].le;
			for(int j = pos; j <= tot; ++j) {
				
			}
		}*/
	}
} 


/*
5
4 4
0 0
1000000000 0
1000000000 1000000000
0 1000000000
1000000001 2
1000000001 -2
1 1000000001
-1 5000000
*/

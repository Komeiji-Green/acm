#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 15020;
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
	ll operator*(const Point& b) const {
		return x*b.x+y*b.y;
	}
	ll operator^(const Point& b) const {
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

int main() {
	int T, m, tot;
	Point v;
	cin >> T;
	while(T--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; ++i) p[i].input();
		for(int i = 1; i <= m; ++i) q[i].input();
		p[n]=p[0]; tot = 0;
		int prev, cur;
		for(int i = 1; i <= m; ++i) {
			v = q[i];
			prev = sgn((p[0]-v)^(p[n-1]-v));
			++tot; uu[tot].id = i;
			for(int j = 0; j < n; ++j) {
				cur = sgn( (p[j+1]-v) ^ (p[j]-v) );
				if(prev < 0 && cur > 0) uu[tot].le = j;
				if(prev > 0 && cur < 0) uu[tot].ri = j;
				prev = cur;
			}
		}
		for(int i = 1; i <= tot; ++i) if(uu[i].ri < uu[i].le) uu[i].ri += n;
		for(int i = 1; i <= tot; ++i) uu[tot+i].id=uu[tot].id, uu[tot+i].le = uu[tot].le + n, uu[tot+i].ri=uu[tot].ri + n;
		tot *= 2;
		sort(uu + 1, uu + tot + 1);
		//for(int i = 1; i <= tot; ++i) printf("itv:  le: %d, ri: %d, id: %d\n", uu[i].le, uu[i].ri, uu[i].id);
		vector<int> ans;
		ans.resize(m + 1);
		for(int i = 1; i <= m; ++i) {
			vector<int> tmp;
			int nowr = uu[i].ri, t = uu[i].le + n;
			int j = i + 1;
			int now = i;
			tmp.push_back(uu[i].id);
			bool f = 1;
			while(nowr < t) {
				for(;j <= tot && uu[j].le <= nowr; ++j) {
					if(uu[j].ri > uu[now].ri) now = j;
				}
				if(uu[now].ri <= nowr) {
					f = 0; break;
				}
				nowr = uu[now].ri;
				tmp.push_back(uu[now].id);
			}
			if(f && ans.size() > tmp.size()) ans = tmp;
		}
		if(ans.size() == m + 1) {
			printf("-1\n");
		} else {
			printf("%d\n", ans.size());
			for(int i = 0; i < ans.size(); ++i) {
				if(i + 1 == ans.size()) printf("%d\n", ans[i]);
				else printf("%d ", ans[i]);
			}
		}
	}
}

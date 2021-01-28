#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

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
	Point operator -(const Point &b)const{
		return Point(x-b.x,y-b.y);
	} 
	ll operator ^(const Point &b)const{
		return x*b.y - y*b.x;
	}
	ll len() {
		return gcd(abs(x), abs(y));
	}
	void trans() {
		if(y < 0) {
			x = -x; y = -y;
		}
		if(y == 0) x = abs(x);
	}
};
const int maxn = 233333;
int s[maxn];
int main() {
	int T;
	ll n, dx1, dy1, dx2, dy2;
	cin >> n;
	Point v1, v2;
	v1.input(); v2.input();
	// S = in + e - 1
	ll in = 0, e = 0, S = 0;
	e = v1.len() + v2.len();
	S = abs(v1^v2);
	if(!S) { // pingxing
		printf("NO\n");
	} else {
		in = S - e + 1;
		ll sum = e - 1 + in;
		if(sum == n) {
			printf("YES\n");
			Point tmp;
			v1.trans(); v2.trans();
			if(sgn(v1 ^ v2) < 0) {
				tmp = v1;
				v1 = v2;
				v2 = tmp;
			}
			ll y = v2.y;
			ll ccc = 0;
			for(ll j = 0, i; j < y; ++j) {
				i = j * v2.x / v2.y;
				if(v2.x > 0 && j * v2.x != i * v2.y) ++i;
				ll son = (j - v1.y) * v2.x;
				ll ri = son / v2.y + v1.x;
				if((ri - v1.x) * v2.y == son) --ri;
				else if(son < 0) --ri;
				for(; i <= ri; ++i) {
					printf("%lld %lld\n", i, j);
					//++ccc;
				}
			}
			//printf("%lld : %lld\n", ccc, sum);
			//bool chk = (x * y == sum);
			//printf("test: %d\n", chk);
			/*for(int i = 0; i < x; ++i) for(int j = 0; j < y; ++j) {
				printf("%lld %lld\n", i, j);
			}*/
		} else {
			printf("NO\n");
		}
	}
}

/*
5
-355 1005
20224 150 // ???

5
-355 10050
20224 150
5
3355 1005
2022 150
*/

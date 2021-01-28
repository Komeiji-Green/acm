#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double inf = 1e20;

int gcd(int a, int b) {
	return a == 0 ? b : gcd(b % a, a);
}
double dist(double x, double y) {
	return hypot(x, y);
}
ll n, m;
bool chk(ll x, ll y) {
	return abs(gcd(x, y)) == 1 && abs(gcd(n-x, m-y))==1;
}
double calc(ll x, ll y) {
	return dist(x, y) + dist(n-x,m-y);
}
double ans;
void gao() {
	for(ll x = 0, y; x <= n; ++x) {
		y = (m * x) / n;
		//printf("tt: %lld %lld\n", x, y);
		if(y * n == x * m) {
			if(chk(x, y - 1)) ans = min(ans, calc(x, y - 1));
			if(chk(x, y + 1)) ans = min(ans, calc(x, y + 1));
		} else {
			if(chk(x, y)) ans = min(ans, calc(x, y));
			if(chk(x, y + 1)) ans = min(ans, calc(x, y + 1));
		}
	}
}
int main() {
	int T;
	cin >> T;
	while(T--) {
		scanf("%lld %lld", &n, &m);
		if(gcd(n, m) == 1) {
			ans = dist(n, m);
		} else {
			ans = inf;
			gao();
			swap(n, m); 
			gao();
		}
		printf("%.15f\n", ans);
	}
} 

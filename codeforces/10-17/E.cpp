#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
ll n, k, sum;
ll a[maxn];

struct DD {
	DD() {
	}
	DD(ll _d, ll _l, ll _w) {
		d = _d, l = _l, w = _w;
	}
	ll d, l, w;
	bool operator< (const DD& b) const {
		return w < b.w;
	}
	void output() {
		printf("len: %lld d: %lld w: %lld\n", l, d, w);
	}
};

inline ll sqr(ll x) {
	return x * x;
}
inline ll calc(ll l, ll d) {
	ll r = l % d, q = l / d;
	return r * sqr(q + 1) + (d - r) * sqr(q);
}
bool chk(ll mid) {
	ll m = sum - mid;
	if(m <= 0) return true;
	priority_queue<DD> q;
	for(int i = 1; i <= n; ++i) {
		q.push(DD(1, a[i], calc(a[i], 1) - calc(a[i], 2)));
	}
	ll sz = k - n;
	DD cur;
	for(ll i = 1; i <= sz; ++i) {
		cur = q.top(); q.pop();
		//cur.output();
		m -= cur.w;
		++cur.d;
		cur.w = calc(cur.l, cur.d) - calc(cur.l, cur.d + 1);
		if(m <= 0) return true;
		q.push(cur);
	}
	return false;
}
int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	sum = 0;
	for(int i = 1; i <= n; ++i) {
		sum += a[i] * a[i];
	}
	ll le = 0, ri = 1e18;
	ll mid = (le + ri) >> 1;
	while(le < ri) {
		//printf("%lld: %d\n", mid, flag);
		if(chk(mid)) {
			ri = mid;
		} else {
			le = mid + 1;
		}
		mid = (le + ri) >> 1;
	}
	printf("%lld\n", mid);
	//printf("%lld\n", calc(a[1], k));
	//printf("%lld %lld %lld\n", calc(19, 1), calc(19, 2), calc(19, 3));
}

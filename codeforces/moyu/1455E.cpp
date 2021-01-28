#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF= 0x3f3f3f3f3f3f3f3f;

struct Point {
	ll x, y;
	void input() {
		scanf("%lld%lld", &x,&y);
	}
} p[10], q[10];
inline ll calc(ll a, ll b, ll c, ll d, ll x1, ll x2) {
	return abs(a-x1)+abs(b-x1)+abs(c-x2)+abs(d-x2);
}
inline ll MIN(ll a, ll b) {
	return a < b ? a : b;
}
ll gao(ll a, ll b, ll c, ll d, ll len) {
	ll ans = calc(a, b, c, d, a, a + len);
	ans = MIN(ans, calc(a, b, c, d, a, a - len));
	ans = MIN(ans, calc(a, b, c, d, b, b + len));
	ans = MIN(ans, calc(a, b, c, d, b, b - len));
	ans = MIN(ans, calc(a, b, c, d, c + len, c));
	ans = MIN(ans, calc(a, b, c, d, c - len, c));
	ans = MIN(ans, calc(a, b, c, d, d + len, d));
	ans = MIN(ans, calc(a, b, c, d, d - len, d));
	return ans;
}
inline ll chk(ll len) {
	return gao(q[1].x, q[2].x, q[3].x, q[4].x, len) + gao(q[1].y, q[3].y, q[2].y, q[4].y, len);
}
void rg(ll a, ll b, ll c, ll d, ll &minl, ll &maxl) {
	ll l1 = min(a, b), r1 = max(a, b);
	ll l2 = min(c, d), r2 = max(c, d);
	if(r1 < l2) minl = l2 - r1;
	else if(r2 < l1) minl = l1 - r2;
	else minl = 0;
	maxl = max(r2 - l1, r1 - l2);
}
int pos[55][10], o[10];
int main() {
	int T;
	cin >> T;
	
	for(int i = 1; i <= 4; ++i) o[i] = i;
	int cnt = 0;
	do {
		++cnt;
		for(int i = 1; i <= 4; ++i) pos[cnt][i] = o[i];
	} while(next_permutation(o + 1, o + 5));
	/*for(int i = 1; i <= cnt; ++i) {
		for(int j = 1; j<= 4; ++j) printf("%d ", pos[i][j]);
		printf("\n");
	}*/
	
	ll cur, ans = 0;
	while(T--) {
		p[1].input(); p[2].input(); p[3].input(); p[4].input();
		ans = INF;
		for(int id = 1; id <= cnt; ++id) {
			for(int i = 1; i <= 4; ++i) q[i] = p[pos[id][i]];
			cur = 0;
			/*ll le = 0ll, ri = 1000000000ll;
			ll mid = (le + ri + 1) >> 1, mmid = (le + mid) >> 1;
			while(le < ri) {
				if(chk(mmid) > chk(mid)) {
					le = mmid + 1;
				} else {
					ri = mid - 1;
				}
				mid = (le + ri + 1) >> 1; mmid = (le + mid) >> 1;
			}*/
			ll l1, r1, l2, r2;
			rg(q[1].x, q[2].x, q[3].x, q[4].x, l1, r1);
			rg(q[1].y, q[3].y, q[2].y, q[4].y, l2, r2);
			cur = min(min(chk(l1), chk(l2)), min(chk(r1), chk(r2)));
			//cur = chk(mid);
			ans = min(ans, cur);
		}
		printf("%lld\n", ans);
	}
}

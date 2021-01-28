#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll a[maxn], b[maxn];

ll gao(ll *v, int l, int r) {
	if(l > r) return 0;
	if(l == r) return v[l];
	int mid = (l + r) / 2;
	ll le = gao(v, l, mid);
	ll ri = gao(v, mid + 1, r);
	return gcd(le, ri);
}
int main() {
	int T;
	int n, m; cin >> n >> m;
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; ++i) scanf("%lld", &b[i]);
	for(int  i =2; i <= n; ++i) a[i] = abs(a[i] - a[1]);
	ll dd = gao(a, 2, n);
	for(int i = 1; i<= m; ++i) {
		ll res =gcd(a[1] + b[i], dd);
		printf("%lld ", res);
	}
	printf("\n");
} 

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
bool vis[1001][100001];

const int maxn = 233333;
struct Point {
	int col;
	ll val;
	bool operator<(const Point& b) {
		return val < b.val || val == b.val && col < b.col;
	}
	bool operator==(const Point& b) {
		return val == b.val;
	}
} v[maxn], u[maxn];

vector<ll> tmp[maxn], vec[maxn];
int main() {
	int T, n, k;
	cin >> T;
	int tot, cnt;
	while(T--) {
		tot = 0;
		cnt = 0;
		scanf("%d", &n);
		ll x;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &k);
			//vec[i].resize(k + 1);
			for(int j = 1; j <= k; ++j) {
				v[++tot].col = i;
				scanf("%lld", &x);
				v[tot].val = x;
			}
		}
		sort(v + 1, v + tot + 1);
		int j = 1;
		vec[1].push_back(v[1].col);
		for(int i = 2; i <= tot; ++i) {
			if(v[i].val != v[j].val) {
				v[++j] = v[i];
			}
			v[j].push_back(v[i].col);
		}
		tot = j;
		
	}
}

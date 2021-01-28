#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 520000;
int *ptr[maxn*100];
int val[maxn*100], tot; 
int f[maxn], o[maxn], h[maxn];
void push(int *p) {
	++tot;
	ptr[tot]=p; val[tot]=*p;
}
void pop() {
	if(tot) {
		*ptr[tot] = val[tot];
		--tot;
	} 
}
int find(int x) {
	return f[x] == x ? x : find(f[x]);
}
void mg(int fx, int fy) {
	if(!fx || !fy) return;
	if(h[fx] < h[fy]) {
		push(&f[fx]);
		f[fx] = fy;
	} else if(h[fx] == h[fy]) {
		push(&f[fx]); push(&h[fy]);
		f[fx] = fy;
		h[fy]++;
	} else {
		push(&f[fy]);
		f[fy] = fx;
	}
}
bool merge(int x, int y) {
	//printf("in: %d %d\n", x, y);
	int fx = find(x); int fy = find(y);
	//printf("in: %d %d\n", fx, fy);
	if(fx == fy) return false;
	if(o[fx] == fy) return true;
	// fx -- o[fy], fy -- o[fx]
	mg(fx, o[fy]); mg(fy, o[fx]);
	fx = find(fx); fy = find(fy);
	push(&o[fx]); push(&o[fy]);
	o[fx] = fy; o[fy] = fx;
	return true;
}
int c[maxn];
struct Edge{
	int u, v;
	bool operator< (const Edge& b) {
		return c[u] == c[b.u]? c[v] < c[b.v] : c[u] < c[b.u];
	}
	bool operator==(const Edge& b) {
		return c[v] == c[b.v] && c[u] == c[b.u];
	}
} e[maxn];
int en;
bool ban[maxn];
ll cnt, ans;
int main() {
	ll n, m, k;
	cin >> n >> m >> k;
	tot = 0;
	for(int i = 1; i <= n; ++i) h[i] = 1, f[i] = i;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &c[i]);
	}
	cnt = k;
	ans = k * (k - 1) / 2;
	for(int i = 1, u, v; i <= m; ++i)  {
		scanf("%d %d", &u, &v);
		if(c[u] == c[v]) {
			if(!ban[c[u]] && !merge(u, v)) {
				ban[c[u]] = true; cnt--;
			}
		} else {
			++en;
			if(c[u] > c[v]) swap(u, v);
			e[en].u=u; e[en].v=v;
		}
	}
	ans = cnt * (cnt - 1) / 2;
	sort(e + 1, e + en + 1); e[0].u = e[0].v = 0;
	int dd = tot; bool flag = true;
	for(int i = 1, u, v; i <= en; ++i) {
		if(!(e[i] == e[i-1])) {
			flag = true;
			while(tot > dd) pop();
		}
		if(flag) {
			u = e[i].u; v = e[i].v;
			if(ban[c[u]] || ban[c[v]]) continue;
			bool ok;
			if(!(ok=merge(u, v))) {
				flag = false;
				--ans;
			}
			//printf("%d: %d %d\n", ok, u, v);
			//for(int i = 1; i <= n; ++i) printf("fa[%d] = %d o[%d] = %d, ", i, f[i], i, o[i]);
			//printf("\n");
		}
	}
	printf("%lld\n", ans);
}


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333, M = 466666;

int n;
int lch[N*20], rch[N*20], t[N*20], num;
void pushup(int k) {
	t[k] = t[lch[k]] + t[rch[k]];
}
void add(int &k, int x, int l, int r) {
	if(!k) k = ++num;
	if(l == r) ++t[k];
	else {
		int mid = ((l+r)>>1);
		if(x <= mid) add(lch[k], x, l, mid);
		else add(rch[k], x, mid + 1, r);
		pushup(k);
	}
}
int query(int k, int L, int R, int l, int r) {
	if(!k) return 0;
	if(L <= l && r <= R) return t[k];
	int mid = ((l+r)>>1);
	int res = 0;
	if(L <= mid) res += query(lch[k], L, R, l, mid);
	if(R > mid) res += query(rch[k], L, R, mid + 1, r);
	return res;
} 
int rt[N];

struct Edge {
	int to, pre;
} e[M];
int last[N], tot;
void ine(int a, int b) {
	++tot;
	e[tot].to = b; e[tot].pre = last[a];
	last[a] = tot;
}
inline void ine2(int a, int b) {
	ine(a, b); ine(b, a);
}
#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)
int a[N], tmp[N];

int dfn[N], las[N], clc;
void change(int x, int dad) {
	dfn[x] = ++clc;
	reg(i, x) {
		int y = e[i].to; if(y == dad) continue;
		change(y, x);
	}
	las[x] = clc;
}
int all[N], sum[N], cnt[M];
bool ok[N];
void dfs1(int x, int dad) {
	sum[x] = 1;
	ok[x] = 1;
	reg(i, x) {
		int y = e[i].to; if(y == dad) continue;
		cnt[i] = query(rt[a[x]], dfn[y], las[y], 1, n);
		//printf("%d to %d: %d,,, le: %d, ri: %d, rt: %d\n", x, y, cnt[i], dfn[y], las[y], rt[a[x]]);
		sum[x] += cnt[i];
		dfs1(y, x);
		ok[x] = ok[x] && ok[y];
	}
	if(sum[x] > 1) ok[x] = 0;
	//printf("tt: %d ok: %d sum: %d\n", x, ok[x], sum[x]);
}

int ans = 0;
void dfs2(int x, int dad) {
	if(all[a[x]] == 1 && ok[x]) ++ans;
	//printf("tt: %d: -all %d\n", x, all[a[x]]);
	int uu = 0;
	reg(i, x) {
		int y = e[i].to; if(y == dad) continue;
		if(!ok[y]) {
			++uu;
			//printf("???\n");
		}
	}
	if(uu >= 2) return;
	if(uu == 0) {
		reg(i, x) {
			int y = e[i].to; if(y == dad) continue;
			if(all[a[x]] == 1 + cnt[i]) dfs2(y, x);
		}
	} else if(uu==  1) {
		reg(i, x) {
			int y = e[i].to; if(y == dad || ok[y]) continue;
			if(all[a[x]] == 1 + cnt[i]) dfs2(y, x);
		}
	}
}

int main() {
	cin >> n;
	for(int i = 1; i <= n ;++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) tmp[i] = a[i];
	sort(tmp + 1, tmp + n + 1);
	for(int i = 1; i <= n; ++i) a[i] = lower_bound(tmp + 1, tmp + n + 1, a[i])-tmp;
	//printf("tt\n");
	//for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
	//printf("\n");
	for(int i = 1, u, v; i < n ; ++i) {
		scanf("%d %d", &u, &v);
		ine2(u, v);
	}
	for(int i = 1; i <= n; ++i) all[a[i]]++;
	change(1, 0);
	for(int x = 1; x <= n; ++x) {
		//printf("kkk: %d %d\n", rt[a[x]], dfn[x]);
		//printf("%d\n", dfn[x]);
		add(rt[a[x]], dfn[x], 1, n);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	cout << ans << endl;
}

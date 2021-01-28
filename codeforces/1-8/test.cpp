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

int main() {
	cin >> n;
	int k, x, op, l, r;
	while(~scanf("%d", &op)) {
		if(op == 0) {
			scanf("%d %d", &k, &x);
			add(rt[k], x, 1, n);
		} else {
			scanf("%d %d %d", &k, &l, &r);
			int res = query(rt[k], l,r, 1, n);
			printf("%d\n", res);
		}
	}
}

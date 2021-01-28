#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 533333;

int t[maxn*10], lch[maxn*10], rch[maxn*10], tot = 0;
void pushup(int k) {
	t[k] = max(t[lch[k]], t[rch[k]]);	
}
void upd(int &k, int x, int v, int l, int r) {
	if(!k) k = ++tot;
	if(l == r) t[k] = max(t[k], v);
	else {
		int mid = ((l + r) >> 1);
		if(x <= mid) upd(lch[k], x, v, l, mid);
		else upd(rch[k], x, v, mid + 1, r);
		pushup(k);
	}
}
int query(int k, int L, int R, int l, int r) {
	if(!k) return 0;
	if(L <= l && r <= R) return t[k];
	else {
		int mid = ((l+r)>>1), res = 0;
		if(L <= mid) res = max(res, query(lch[k], L, R, l, mid));
		if(R > mid) res = max(res, query(rch[k], L, R, mid + 1, r));
		return res;
	}
}
void clear() {
	for(int i = 0; i <= tot; ++i) t[i]=lch[i]=rch[i]=0;
	tot = 0;
	//printf("clr\n");
}

int a[maxn], nxt[maxn], stk[maxn];
vector<pair<int,int> > vec[maxn]; 
int main() {
	int T, n;
	cin >> T;
	while(T--) {
		clear();
		for(int i = 1; i <= n; ++i) vec[i].clear(); //printf("clr2\n");
		for(int i = 0; i <= n; ++i) nxt[i] = 0;// printf("clr3\n");
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		int top = 0;
        a[n+1] = n+1;
		for(int i = 1; i <= (n+1); ++i) {
			for(;top && a[stk[top]] < a[i]; --top) nxt[stk[top]] = i;
			stk[++top] = i; 
		}
		int rt = 1;
		upd(rt, min(a[1],a[2]), 2, 1, n + 1);
		if(nxt[2]) vec[nxt[2]].push_back(make_pair(a[2], 2 + 1));
		for(int i = 3; i <= n + 1; ++i) {
			int cur = query(1, 1, a[i], 1, n + 1) + 1; 
			upd(rt, a[i], cur, 1, n + 1);
			for(auto pr : vec[i]) {
				upd(rt, pr.first, pr.second, 1, n + 1);
				//cur = max(cur, pr.second);
				//printf("!!\n");
			}
			if(nxt[i]) vec[nxt[i]].push_back(make_pair(a[i], cur + 1));
		}
		int ans= query(1, 1, n + 1, 1, n + 1);
		printf("%d\n", ans - 1);
	}
}

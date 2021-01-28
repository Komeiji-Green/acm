#include<bits/stdc++.h>
using namespace std;

const int maxn = 233333;

struct DD {
	int v, pre;
	bool operator< (const DD& b) const {
		return pre < b.pre;
	}
} dd[maxn];
int la[maxn];

struct Segment_Tree {
	int ch[maxn*60][2], sum[maxn*60], tot;
	Segment_Tree(): tot(0) {}
	void Pushup(int k) {
		sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
	}
	void add(int &k, int x, int l, int r) {
		if(!k) k = ++tot;
		if(l == r) ++sum[k];
		else {
			int m = l + ((r - l) >> 1);
			if(x <= m) add(ch[k][0], x, l, m);
			else add(ch[k][1], x, m + 1, r);
			Pushup(k);
		}
	}
	int query(int k, int L, int R, int l, int r) {
		if(!k) return 0;
		if(L <= l && r <= R) return sum[k];
		else {
			int m = l + ((r - l) >> 1);
			int res = 0;
			if(L <= m) res += query(ch[k][0], L, R, l, m);
			if(R > m) res += query(ch[k][1], L, R, m + 1, r);
			return res;
		}
	}
} ST;

int rt[maxn], n;
void add(int prev, int v) {
	for(register int i = prev; i <= (n + 1); i += i & (-i)) {
		ST.add(rt[i], v, 1, n);
	}
}
int query(int prev, int l, int r) {
	int res = 0;
	for(register int i = prev; i; i -= i & (-i)) {
		res += ST.query(rt[i], l, r, 1, n);
	}
	return res;
}

bool chk(int le, int ri, int m) {
	if(le > ri) return false;
	int res = query(le, le, ri);
	//printf("le: %d, ri: %d, mex: %d, res: %d\n", le, ri, m, res);
	return res == m - 1;
}

vector<int> li[maxn];
int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &dd[i].v);
	}
	for(int i = 1; i <= n; ++i) {
		dd[i].pre = la[dd[i].v] + 1;
		la[dd[i].v] = i;
	}
	for(int i = 1; i <= n; ++i) {
		li[dd[i].v].push_back(i);
	}
	for(int i = 1; i <= (n + 1); ++i) {
		li[i].push_back(n + 1);
	}
	int m = 1;
	for(m = 1; m <= (n + 1); ++m) {
		int last = 0;
		bool flag = false;
		for(auto i : li[m]) {
			if(chk(last + 1, i - 1, m)) {
				flag = true;
				break;
			}
			last = i;
		}
		if(!flag) break;
		for(auto i : li[m]) {
			if(i <= n) add(dd[i].pre, i);
		}
	}
	printf("%d\n", m);
} 

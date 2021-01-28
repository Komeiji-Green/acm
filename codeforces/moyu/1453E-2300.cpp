#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

const int M = 433333, N = 233333;
const int INF = 0x3f3f3f3f;
struct Edge {
	int from, to, pre;
} e[M];
int last[N], tot;
void ine(int a, int b) {
	++tot;
	e[tot].from = a; e[tot].to = b; e[tot].pre = last[a];
	last[a] = tot;
}
inline void ine2(int a, int b) {
	ine(a, b); ine(b, a);
}
#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)
int n, L;
int minv[N];
bool chk(int x, int dad) {
	minv[x] = INF;
	int cnt = 0, ch = 0;
	reg(i, x) {
		int y = e[i].to; if(y == dad) continue;
		++ch;
		if(!chk(y, x)) return false;
		if(minv[y] + 1 > L) return false;
		if(minv[y] + 1 == L) {
			if((++cnt) > 1) return false;
			minv[x] = L;
		} else if(!cnt) {
			minv[x] = min(minv[x], minv[y] + 1);
		}
	}
	if(ch == 0) minv[x] = 0;
	return true;
}

int main() {
	int T, u, v;
	cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i <= tot; ++i) last[i] = 0;
		tot = 0;
		for(int i = 1; i < n; ++i) {
			scanf("%d %d", &u, &v);
			ine2(u, v);
		}
		int le = 1, ri = n - 1;
		int mid = (le + ri) >> 1;
	
		while(le < ri) {
			L = mid;
			if(chk(1, 0)) {
				ri = mid;
			} else {
				le = mid + 1;
			}
			mid = (le + ri) >> 1;
		}
		printf("%d\n", mid);
	}
} 

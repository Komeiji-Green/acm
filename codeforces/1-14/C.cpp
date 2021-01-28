#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int d1[maxn], x1[maxn], d2[maxn], x2[maxn], v[maxn];
char s[maxn];
int main() {
	int T, n, m;
	cin >> T;
	while(T--) {
		scanf("%d %d", &n, &m);
		scanf("%s", s + 1);
		d1[0] = x1[0] = v[0] = 0;
		for(int i = 1; i <= n; ++i) {
			if(s[i] == '+') v[i] = v[i-1] + 1;
			else v[i] = v[i-1] - 1;
			d1[i] = max(d1[i-1], v[i]);
			x1[i] = min(x1[i-1], v[i]);
		}
		d2[n+1] = x2[n+1] = 0;
		for(int i = n; i >= 1; --i) {
			if(s[i] == '+') {
				d2[i] = 1 + d2[i+1];
				x2[i] = min(0, 1 + x2[i+1]);
			} else {
				d2[i] = max(0, d2[i+1] - 1);
				x2[i] = min(0, x2[i+1] - 1);
			}
		}
		int l , r;
		while(m--) { 
			scanf("%d%d", &l, &r);
			int ri = max(d1[l-1], v[l-1] + d2[r+1]);
			int le = min(x1[l-1], v[l-1] + x2[r+1]);
			printf("%d\n", ri - le + 1);
		}
	}
} 

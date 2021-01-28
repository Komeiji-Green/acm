#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int s[maxn];
int main() {
	int T;
	int n, m, a, b;
	cin >> T;
	while(T--) {
		scanf("%d %d %d %d", &n, &m, &a, &b);
		for(int i = 1; i <= m; ++i) scanf("%d", &s[i]);
		sort(s + 1, s + m+ 1);
		int num = abs(a - b) - 1;
		int tm;
		if(a < b) tm = a + num - 1;
		else tm = n - a + 1 + num - 1;
		//int idx = upper_bound(s + 1, a + m+ 1, tm) - a;
		int cnt = 0;
		for(int i = min(m, num); i >= 1; --i) {
			if(s[i] <= tm) {
				++cnt; --tm;
			}
		}
		printf("%d\n", cnt);
	}
}

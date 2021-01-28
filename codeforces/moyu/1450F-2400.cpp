#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn], cnt[maxn];
int main() {
	int T;
	cin >> T;
	int n;
	while(T--) {
		scanf("%d", &n);
		int k = 1;
		for(int i = 1; i <= n; ++i) cnt[i] = 0;
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for(int i = 1; i < n; ++i)
			if(a[i] == a[i + 1]) {
				cnt[a[i]] += 2; ++k;
			}
		cnt[a[1]]++; cnt[a[n]]++;
		int maxv = 0, idx = 0;
		for(int i = 1;i <= n; ++i) {
			if(cnt[i] > maxv) {
				maxv = cnt[i]; idx = i;
			}
		}
		int dd = 0;
		for(int i = 1; i < n; ++i)
			if(a[i] != a[i + 1] && a[i] != idx && a[i + 1] != idx)
				++dd;
		if(maxv - 1 <= k) {
			printf("%d\n", k - 1);
		} else if((maxv - 1) <= (k + dd)) { // ¿ÉÐÐ 
			printf("%d\n", maxv - 2);
		} else {
			printf("-1\n");
		}
	}
}

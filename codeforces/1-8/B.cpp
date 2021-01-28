#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 500005;

ll a[maxn];
bool v[maxn];
int n;
int chk(int i) {
	if(i <= 1 || i >= n ) return 0;
	return a[i] > a[i-1] && a[i] > a[i+1] || a[i] < a[i-1] && a[i] < a[i+1];
}
int main() {
	int T;
	cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i=1;i<=n;++i) scanf("%lld", &a[i]);
		int sum = 0;
		for(int i = 1; i <=n;++i) v[i] = 0;
		for(int i=2; i < n; ++i) {
			if(a[i] > a[i-1] && a[i] > a[i+1] || a[i] < a[i-1] && a[i] < a[i+1]) {
				++sum;
				v[i] = true;
			}
		}
		int w = 0;
		ll o;
		for(int i = 2, mi; i < n; ++i) {
			mi = 1;
			o = a[i];
			a[i] = a[i-1]; mi = min(mi, chk(i+1));
			a[i] = a[i+1]; mi = min(mi, chk(i-1));
			a[i] = o;
			mi -= (chk(i-1) + chk(i) + chk(i+1));
			w = min(w, mi);
		}
		printf("%d\n", sum + w);
	}
}






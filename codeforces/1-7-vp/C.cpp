#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn =  233333;
ll h[maxn], p[maxn];
int main() {
	int T;
	cin >> T;
	while(T--) {
		int n; ll k;
		scanf("%d %lld", &n, &k); 
		for(int  i = 1; i <= n; ++i) scanf("%lld", &h[i]);
		p[1] = h[1];
		ll low, up;
		bool f = 1;
		for(int i = 2; i < n; ++i) {
			low = max(h[i], p[i-1]-k+1);
			up = min(h[i] + k-1, p[i-1]+k-1);
			if(low > up) {
				f = 0; break;
			}
			if(h[i+1] < low) {
				p[i] = low;
			} else if(h[i+1] <= up) {
				p[i] = h[i+1];
			} else {
				p[i] = up;
			}
		}
		if(n > 1) {
			low = max(h[n], p[n-1]-k+1);
			up = min(h[n], p[n-1]+k-1);
			if(low > up) f = 0;
		}
		if(f) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
		
	}
} 

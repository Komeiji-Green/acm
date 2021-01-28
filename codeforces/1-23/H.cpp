#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int b[maxn];
int main() {
	int T;
	cin >> T;
	while(T--) {
		int n, k, m;
		scanf("%d%d%d",&n,&k,&m);
		for(int i= 1; i <= m; ++i) scanf("%d", &b[i]);
		if((n-m)%(k-1)) {
			printf("NO\n");
		} else {
			int le = 1, ri = m;
			int sum = 0, hf = (k-1)/2;
			b[0] = 0; b[m+1] = n + 1;
			for(; le <= m; ++le) {
				sum += b[le]-b[le-1]-1;
				if(sum >= hf) break;
			}
			sum=0;
			for(; ri >= 1; --ri) {
				sum += b[ri+1]-b[ri]-1;
				if(sum >= hf) break;
			}
			if(le <= ri) {
				printf("YES\n");
			} else {
				printf("NO\n");
			}
		}
	}
} 

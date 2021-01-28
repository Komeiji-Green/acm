#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn =  233333;
ll p[10] = {2, 4, 16, 256, 65536};
int op[maxn][2];
int main() {
	int T;
	cin >> T;
	while(T--) {
		ll n;
		scanf("%lld", &n);
		int tot = 0 ;
		for(int i = 4; i >= 0; --i) {
			if(n > p[i]) {
				for(int j = p[i] + 1; j < n; ++j) {
					++tot;
					op[tot][0] = j;
					op[tot][1] = n;
				}
				++tot;
				op[tot][0] = n;
				op[tot][1] = p[i];
				++tot;
				op[tot][0] = n;
				op[tot][1] = p[i];
				n = p[i];
			}
		}
		printf("%d\n", tot);
		for(int i = 1; i <= tot; ++i) {
			printf("%d %d\n", op[i][0], op[i][1]);
		}
	}
} 

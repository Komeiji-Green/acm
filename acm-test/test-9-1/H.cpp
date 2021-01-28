#include <iostream>
#include <algorithm>
//#include <cstring>
using namespace std;

const int N = 2333;
int p[N], a[N], tot = 0;
int main() {
	int T;
	cin >> T;
	while(T--) {
		memset(p, 0, sizeof(p));
		memset(a, 0, sizeof(a));
		tot = 0;
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &p[i]);
		}
		sort(p + 1, p + n + 1);
		p[0] = 0;
		for(int i = n; i >= 1; i-=2) {
			a[++tot] = p[i] - p[i - 1] - 1;
		}
		int sg = 0;
		for(int i = 1; i <= tot; i++) {
			sg ^= a[i];
		}
		if(sg) {
			printf("Georgia will win\n");
		} else {
			printf("Bob will win\n");
		}
	}
} 

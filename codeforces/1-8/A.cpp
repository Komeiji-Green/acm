#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2300000;

char str[maxn];
int sa[maxn], rk[maxn], h[maxn];
int main() {
	int T;
	cin >> T;
	while(T--) {
		int n;
		scanf("%d", &n);
		if(n == 1) {
			printf("9\n");
		} else if(n == 2) {
			printf("98\n");
		} else {
			printf("98");
			for(int i = 9, j = 3; j <= n; ++j, i = (i+1)%10) {
				printf("%d", i);
			}
			printf("\n");
		}
	}
}






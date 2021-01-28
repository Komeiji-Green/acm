#include<bits/stdc++.h>
using namespace std;
int main() {
	int T, n;
	cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = n + 1; i <= 2 * n; ++i) {
			printf("%d ", 2 * i);
		}
		printf("\n");
	}
}

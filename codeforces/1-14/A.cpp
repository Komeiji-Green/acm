#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int a[20003];
int main() {
	int T, n, d;
	cin >> T;
	while(T--) {
		scanf("%d %d", &n, &d);
		for(int i = 1; i<= n ;++i) scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		if(a[n] <= d || a[1] + a[2] <= d) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
} 

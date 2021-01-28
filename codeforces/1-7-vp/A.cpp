#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

char s[23333];
int main() {
	int T;
	cin >> T;
	while(T--) {
		scanf("%s", s);
		int le, ri;
		int n = strlen(s);
		for(int i = 0; i < n; ++i) {
			if(s[i] == '(') le = i;
			if(s[i] == ')') ri = i;
		}
		if(n % 2) {
			printf("NO\n"); continue;
		} 
		if(le == n - 1 || ri == 0) {
			printf("NO\n"); continue;
		} else {
			printf("YES\n");
		}
		
	}
} 

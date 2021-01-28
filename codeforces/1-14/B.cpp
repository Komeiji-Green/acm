#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

char s[200], t[200];

int gao(char *s, int n) {
	int i;
	for(i = 1; i < n; ++i) {
		if(n % i) continue;
		bool f = 1;
		for(int j = i; j < n; ++j) {
			if(s[j] != s[j-i]) {
				f = 0;break;
			}
		}
		if(f) break;
	}
	return i;
}
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int cmp(char *s, char *t, int n) {
	for(int i = 0; i < n; ++i) {
		if(s[i] != t[i]) return 0;
	}
	return 1;
}
int main() {
	int T, n, d;
	cin >> T;
	while(T--) {
		scanf("%s %s", &s, &t);
		int n = strlen(s), m = strlen(t);
		int a = gao(s, n), b = gao(t, m);
		if(a == b && cmp(s, t, a)) {
			int nn = n / a, mm = m / a;
			int len = nn * mm / gcd(nn, mm);
			s[a] = '\0';
			for(int i = 1; i <= len; ++i) {
				printf("%s", s);
			}
			printf("\n");
		} else {
			printf("-1\n");
		}
	}
} 

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
int a[N];
char s[N];
int t[N];
int main() {
	int T;
	cin >> T;
	int n;
	while(T--) {
		scanf("%d%s", &n, s);
		t[0] = 1;
		for(int i = 1, j = 1 + s[0] - '0'; i < n; ++i) {
			int k = s[i] - '0';
			for(int d = 1; d >= 0; --d) {
				if(k + d != j) {
					t[i] = d; 
					j = k + d;
					break;
				}
			}
			/*if(k == j) {
				t[i] = 1; j = k + 1;
			} else {
				t[i] = 0; j = k;
			}*/
		}
		for(int i = 0; i < n; ++i) printf("%d", t[i]);
		printf("\n");
	}
} 

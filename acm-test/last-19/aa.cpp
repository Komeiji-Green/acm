#include<iostream>
using namespace std;

const int N = 1050;
int mm[N];
bool dp[N][N][12];
char s[N][N];

void initrmq(int m, int n) {
	mm[0] = -1;
	for(int i = 1; i <= n; i++) {
		if(i & (i - 1)) mm[i] = mm[i - 1];
		else mm[i] = mm[i - 1] + 1;
	}
	
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			dp[i][j][0] = s[i][j] == '0';
		}
	}
	
	for(int k = 1; k <= 10; k++) {
		for(int i = 1; i <= m; i++) {
			for(int j = 1; j <= n; j++) {
				
			}
		}
	}
	
}
int main() {
	
}

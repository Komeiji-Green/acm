#include<bits/stdc++.h>
using namespace std;

const int maxn = 2004000;
char s[maxn];
bool vis[7][7];
int id[300];
int a[10];
int main() {
	int T;
	cin >> T;
	while(T--) {
		memset(vis, 0, sizeof(vis));
		for(int i = 1; i <= 6; ++i) {
			scanf("%s", s);
			for(int j = 0; s[j]; ++j) {
				if(s[j] == 'h') {
					vis[i][1] = 1;
				} else if(s[j] == 'a') {
					vis[i][2] = 1;
				} else if(s[j] == 'r') {
					vis[i][3] = 1;
				} else if(s[j] == 'b') {
					vis[i][4] = 1;
				} else if(s[j] == 'i') {
					vis[i][5] = 1;
				} else if(s[j] == 'n') {
					vis[i][6] = 1;
				}
			}
		}
		/*for(int i = 1; i <= 6; ++i) {
		for(int j = 1; j <= 6; ++j) {
			printf("%d ", vis[i][j]);
		}
		printf("\n");
	}*/
		for(int i = 1; i <= 6; ++i) a[i] = i;
		bool flag = false;
		do {
			flag = true;
			for(int i = 1; i <= 6; ++i) {
				if(!vis[i][a[i]]) {
					flag = false; break;
				} 
			}
		} while(next_permutation(a + 1, a + 7) && !flag);
		if(flag) {
			printf("Yes\n");
		} else {
			printf("No\n"); 
		}
	}
} 

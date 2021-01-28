#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int prex[60], prey[60];
int bit[50];
int mx, my, maxp;
int main() {
	int T, x, y;
	///printf("%d\n", (1<<30));
	cin >> T;
	for(int i = 1; i <= 31; ++i) bit[i] = 1<<(i-1);
	for(int i = 1; i <= 31; ++i) mbit[i] = mbit[i-1] + bit[i];
	while(T--) {
		scanf("%d%d", &x, &y);
		prex[0] = prey[0] = 0; xb[0] = x; yb[0] = y;
		for(int i = 1; i <= 31; ++i) {
			xb[i]=((~mbit[i])&x);
			if(bit[i]&x) prex[i] = prex[i-1]+1;
			else prex[i] = prex[i-1];
		}
		for(int i = 1; i <= 31; ++i) {
			yb[i]=((~mbit[i])&y);
			if(bit[i]&y) prey[i] = prey[i-1]+1;
			else prey[i] = prey[i-1];
		}
		mx = prex[31]; my = prey[31];
		
		for(int i = 1; i <= 31; ++i) for(int j = 1; j <= 31; ++j) {
			if((bit[i]&x)&&(bit[j]&y) && (xb[i]&yb[j]) == 0)) {
				if(i > j) {
					cnt += p[prey[i-1]-prey[j-1]]*p_3[j-1];
				} else {
					cnt += p[prex[j-1]-prex[i-1]]*p_3[i-1];
				}
			}
		}
		for(int j = 1; j <= 31; ++j) {
			if((bit[j]&y)&&(x&yb[j])==0) {
				cnt += p[prex[j-1]];
			}
		} 
		for(int i = 1; i <= 31; ++i) {
			if((bit[i]&x)&&(y&xb[i])==0) {
				cnt += p[prey[i-1]];
			}
		}
	}
}

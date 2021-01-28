#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
char r[maxn], b[maxn];
int main() {
	int T;
	cin >> T;
	int n;
	while(T--) {
		scanf("%d", &n);
		scanf("%s%s", r, b);
		int rr = 0,  bb = 0;
		for(int i = 0; i < n; ++i) {
			if(r[i] > b[i]) ++rr;
			else if(r[i] < b[i]) ++bb;
		}
		if(rr > bb) {
			printf("RED\n");
		} else if(rr == bb) {
			printf("EQUAL\n");
		} else {
			printf("BLUE\n");
		}
	}
} 

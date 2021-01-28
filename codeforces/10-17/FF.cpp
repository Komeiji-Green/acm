#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 520000;
char s[maxn];
bool a[maxn];
struct DD {
	int h, pos;
} stk[maxn];
int top = 0;
int main() {
	int n;
	cin >> n;
	scanf("%s", s);
	for(int i = 1; i <= n; ++i) {
		a[i] = s[i - 1] == '1';
	}
	ll ans = 0, sum = 0;
	DD cur;
	for(int i = 1, j = 1; i <= n; ++i) {
		if(!a[i]) {
			ans += sum;
			if(a[i - 1]) ++top;
			//printf("i: %d, sum: %lld\n", i, sum);
		} else {
			if(!a[i - 1]) cur.h = 0;
			++cur.h;
			cur.pos = i;                                       
			while(top && stk[top-1].h < cur.h) --top;
			if(!top) j = 0;
			else j = stk[top-1].pos - cur.h + 1;
			sum += i - j;
			ans += sum;
			stk[top] = cur;
			//printf("i: %d, sum: %lld, j: %d, top: %d\n", i, sum, j, top);
		}
	}
	printf("%lld\n", ans);
}
 

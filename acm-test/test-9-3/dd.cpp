#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 500010;

int s[N];
int w, sa[N], rk[N << 1], oldrk[N << 1];
// 为了防止访问 rk[i+w] 导致数组越界，开两倍数组。
// 当然也可以在访问前判断是否越界，但直接开两倍数组方便一些。

bool cmp(int x, int y) {
	return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
}

void getSA(int n) {
	int i, p;

	for (i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i] + 1;

	for (w = 1; w < n; w <<= 1) {
		sort(sa + 1, sa + n + 1, cmp); 
		memcpy(oldrk, rk, sizeof(rk));
		// 由于计算 rk 的时候原来的 rk 会被覆盖，要先复制一份
		for (p = 0, i = 1; i <= n; ++i) {
			if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
			        oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
				rk[sa[i]] = p;
			} else {
				rk[sa[i]] = ++p;
			}  // 若两个子串相同，它们对应的 rk 也需要相同，所以要去重
		}
	}

	//for (i = 1; i <= n; ++i) printf("%d ", sa[i]);
}

int ans[N], tot = 0;
int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		tot = 0;
		
		for(int i = 1; i <= n; i++) {
			scanf("%d", &s[n + 1 - i]);
		}
		getSA(n);
	
		for(int i = sa[1]; i <= n; i++) {
			ans[++tot] = s[i];
		}
		
		for(int i = 1; i < sa[1]; i++) {
			s[i + sa[1] - 1] = s[i];
		}
		int m = sa[1] - 1;
		getSA(2 * m);
		for(int i = 1; i <= 2 * m; i++) {
			if(sa[i] <= m) {
				for(int j = sa[i]; j < sa[i] + m; j++) {
					ans[++tot] = s[j];
				}
				break;
			}
		}
		for(int i = 1; i <= tot; i++) {
			printf("%d\n", ans[i]);
		}
	}
}



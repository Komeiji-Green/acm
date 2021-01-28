#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 500010;

int s[N];
int w, sa[N], rk[N << 1], oldrk[N << 1];
// Ϊ�˷�ֹ���� rk[i+w] ��������Խ�磬���������顣
// ��ȻҲ�����ڷ���ǰ�ж��Ƿ�Խ�磬��ֱ�ӿ��������鷽��һЩ��

bool cmp(int x, int y) {
	return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
}

void getSA(int n) {
	int i, p;

	for (i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i] + 1;

	for (w = 1; w < n; w <<= 1) {
		sort(sa + 1, sa + n + 1, cmp); 
		memcpy(oldrk, rk, sizeof(rk));
		// ���ڼ��� rk ��ʱ��ԭ���� rk �ᱻ���ǣ�Ҫ�ȸ���һ��
		for (p = 0, i = 1; i <= n; ++i) {
			if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
			        oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
				rk[sa[i]] = p;
			} else {
				rk[sa[i]] = ++p;
			}  // �������Ӵ���ͬ�����Ƕ�Ӧ�� rk Ҳ��Ҫ��ͬ������Ҫȥ��
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



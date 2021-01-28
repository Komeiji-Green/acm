#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 500010;

int rd[N], s[N], real[N];
int n, sa[N], rk[N], oldrk[N << 1], id[N], px[N], cnt[N];
// px[i] = rk[id[i]]（用于排序的数组所以叫 px）

bool cmp(int x, int y, int w)
{
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

void getSA(int n) {
    int i, m = 300000, p, w;
	
	s[n + 1] = 0;
    for (i = 1; i <= n; ++i)
        ++cnt[rk[i] = s[i]];
    for (i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i)
        sa[cnt[rk[i]]--] = i;

    for (w = 1; w < n; w <<= 1, m = p)
    { // m=p 优化计数排序值域
        for (p = 0, i = n; i > n - w; --i)
            id[++p] = i;
        for (i = 1; i <= n; ++i)
            if (sa[i] > w)
                id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i)
            ++cnt[px[i] = rk[id[i]]];
        for (i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i)
            sa[cnt[px[i]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i)
            rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
    }
}

int ans[N], tot = 0;
int main() {
	int n;
	cin >> n;
		tot = 0;
		
		for(int i = 1; i <= n; i++) {
			scanf("%d", &rd[i]);
		}
		memcpy(real, rd, sizeof(rd));
		sort(real + 1, real + n + 1);
		int num = unique(real + 1, real + n + 1) - real;
		for(int i = 1; i <= n; i++) {
			int idx = lower_bound(real + 1, real + num, rd[i]) - real;
			s[i] = idx;
		}
		for(int i = 1, j = n; i < j; i++, j--) {
			swap(s[i], s[j]);
		}
		
		getSA(n);
		
		int ii;
		for(int i = 1; i <= n; i++) {
			if(sa[i] >= 3) {
				ii = sa[i];
				break;
			}
		}
		
		for(int i = ii; i <= n; i++) {
			ans[++tot] = s[i];
		}
		
		for(int i = 1; i < ii; i++) {
			s[i + ii - 1] = s[i];
		}
		int m = ii - 1;
		getSA(2 * m);
		for(int i = 1; i <= 2 * m; i++) {
			if(sa[i] <= m && sa[i] >= 2) {
				for(int j = sa[i]; j < sa[i] + m; j++) {
					ans[++tot] = s[j];
				}
				break;
			}
		}
		for(int i = 1; i <= tot; i++) {
			printf("%d\n", real[ans[i]]);
		}
}

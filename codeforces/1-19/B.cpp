#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1000000 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛法 [1, n] 内素数
void Prime(int n) {
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++) {
            if (1ll * i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
	Prime(100005);
	int T;
	cin >> T;
	int d;
	while(T--) {
		scanf("%d", &d);
		int idx = lower_bound(prime + 1, prime + cnt + 1, d + 1) - prime;
		int p = prime[idx];
		idx = lower_bound(prime + 1, prime + cnt + 1, p + d) - prime;
		int q = prime[idx];
		ll ans = 1ll * p * q;
		printf("%lld\n", ans); 
	}
} 

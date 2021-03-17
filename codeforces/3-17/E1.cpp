#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10000000 + 5;
const int N = 233333;
bool isnt[maxn];
int prime[maxn], minp[maxn];
int cnt = 0;

// 线性筛法 [1, n] 内素数
void Prime(int n) {
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i, minp[i] = i;
        for (int j = 1; j <= cnt; j++) {
            if (1ll * i * prime[j] > n) break;
            isnt[i * prime[j]] = 1, minp[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
}

int p[1005], l[1005];
int gao(int x) {
    int tot = 0; p[0] = 0;
    while(x > 1) {
        if(minp[x] != p[tot]) {
            p[++tot] = minp[x];
            l[tot] = 1;
        } else {
            l[tot]++;
        }
        x /= minp[x];
    }
    int res = 1;
    for(int i = 1; i <= tot; ++i) {
        if(l[i] % 2 == 1) {
            res *= p[i];
        }
    }
    return res;
}
int a[N], b[N], pv[maxn], last[maxn];
int main() {
    Prime(10000001);
    int T, n, k;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &k);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            b[i] = gao(a[i]);
        }
        for(int i = 1; i <= n; ++i) {
            pv[i] = last[b[i]];
            last[b[i]] = i; 
        }
        int ans = 0;
        //printf("pv:\n");
        for(int i = 2, j = 1; i <= n; ++i) {
            //printf("%d ", pv[i]);
            if(pv[i] >= j) {
                ++ans; j = i;
            }
        }
        ++ans;
        //printf("\n");
        for(int i = 1; i <= n; ++i) last[b[i]] = 0;
        printf("%d\n", ans);
    }
}
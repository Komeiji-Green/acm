#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 520000;
const ll inf = 0x3f3f3f3f3f3f3f3f;
ll a[maxn], h[maxn], w[maxn], sum[maxn], pre[maxn], ans = -inf;
int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);
    k = k + 1;
    a[0] = 0; h[0] = -1; w[0] = 0;
    for(int i = 1; i <= n; ++i) {
        h[i]=(i-1)/k; w[i]=h[i]*a[i]+w[i-1]; //printf("(%lld: %lld) ",h[i], w[i]);
    }
    //printf("\n");
    sum[n+1]=0;
    for(int i = n; i >= 0; --i) sum[i]=a[i]+sum[i+1];
    pre[n+1]=0;
    for(int i = n; i >= 0; --i) pre[i] = pre[i + 1] + sum[i];
    ll cur = 0;
    for(int i = 0; i <= n; ++i) {
        cur = w[i] + pre[i+1] + h[i]*sum[i+1]; 
        ans = max(cur, ans);
    }
    printf("%lld\n", ans);
}
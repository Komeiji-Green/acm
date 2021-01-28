#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1000500;
ll a[maxn], b[maxn];
int main() {
    int T;
    cin >> T;
    int n, m, k;
    while(T--) {
        scanf("%d %d %d", &n, &m, &k);
        for(int i = 1; i <= m; i++) {
            scanf("%d", &a[i]);
            b[i] = abs(a[i] - 1) - abs(a[i] - k);
        }
        ll minv = b[1];
        for(int i = 1; i <= m; i++) {
            minv = min(minv, b[i]);
        }
        ll sum = 0;
        for(int i = 1; i <= m; i++) {
            sum += abs(a[i] - k);
        }
        sum *= 2;
        sum += k - 1;
        sum += minv;
        printf("%lld\n", sum);
    }
}
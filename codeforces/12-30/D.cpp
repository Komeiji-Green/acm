#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
struct Node {
    int deg;
    ll w;
    bool operator<(const Node& b) {
        return w < b.w;
    }
} a[maxn];
ll ans[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i = 1; i<= n;++i) scanf("%lld", &a[i].w);
        for(int i=1;i<=n;++i) a[i].deg=0;
        for(int i=2, u,v; i<=n;++i) {
            scanf("%d%d",&u,&v);
            a[u].deg++; a[v].deg++;
        }
        ll sum = 0;
        sort(a + 1, a + n + 1);
        for(int i=1; i<=n; ++i) {
            sum += a[i].deg*a[i].w;
        }
        ans[n-1]=sum;
        //printf("%lld ",sum);
        for(int i=n-2,j=1;i>=1;--i) {
            while(a[j].deg==1)++j;
            a[j].deg--;
            sum-=a[j].w;
            ans[i]=sum;
            //printf("%lld ",sum);
        }
        for(int i = 1; i<=(n-1);++i) printf("%lld ",ans[i]);
        printf("\n");
    }
}
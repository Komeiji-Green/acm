#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 500005;

ll a[maxn], b[maxn], c[maxn];

ll getmin(ll *d, int n) {
	ll mi = d[1];
	for(int i = 2; i <= n; ++i) {
		mi = min(mi, d[i]);
	}
	return mi;
}
ll minv[10];
int main() {

	ll s1, s2, s3;

		int  A, B, C;
		scanf("%d%d%d", &A, &B,&C);
		s1=s2=s3=0;
		for(int i =1; i <= A; ++i) scanf("%lld",&a[i]);
		for(int i =1; i <= B; ++i) scanf("%lld",&b[i]);
		for(int i =1; i <= C; ++i) scanf("%lld",&c[i]);
		for(int i =1; i <= A; ++i) s1+=a[i];
		for(int i =1; i <= B; ++i) s2+=b[i];
		for(int i =1; i <= C; ++i) s3+=c[i];
		minv[1] = getmin(a, A);
		minv[2] = getmin(b, B);
		minv[3] = getmin(c, C);
		sort(minv + 1, minv + 4);
		ll ans1 = s1+s2+s3-2*(minv[1]+minv[2]);
		ll ans2 = max(s1+s2-s3,max(s1-s2+s3, -s1+s2+s3));
		printf("%lld\n", max(ans1,ans2));

}






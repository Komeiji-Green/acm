#include<bits/stdc++.h> 
#define inf 0x7fffffff
#define ll long long
#define MOD 1000000007
using namespace std;
const int maxn=110000;
inline ll read(){
    ll f=1,x=0;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return f*x;
}
 
int n;
ll a[maxn],f[maxn];
 
bool cmp(ll x,ll y){return x>y;}
 
int main(){
	//freopen("text.in","r",stdin);
	//freopen("text1.out","w",stdout);
	n=read();
	for (int i=1;(1<<(i-1))<=maxn;++i)
		for (int j=1<<(i-1);j<min(1<<i,maxn);++j)f[j]=i;
	for (int i=1;i<=n;++i)a[i]=read();
	sort(a+1,a+1+n,cmp);
	int i=2;
	while (i<=n&&a[i]==a[i+1])++i;
	if (i>2&&a[1]==a[2]){
		printf("0\n");
		return 0;
	}
	ll ans=0,d=0;
	while (i<n){
		if (a[2]+d+(f[i-1]-1)*(a[i]-a[i+1])>a[1]){
			ans+=f[i-1]*((a[1]-a[2]-d)/(f[i-1]-1));
			ans+=(a[1]-a[2]-d)%(f[i-1]-1);
			printf("%lld\n",ans);
			return 0;
		}
		ans+=f[i-1]*(a[i]-a[i+1]);
		d+=(f[i-1]-1)*(a[i]-a[i+1]);
		++i;
		while (i<=n&&a[i]==a[i+1])++i;
	}
	ans+=f[n-1]*((a[1]-a[2]-d)/(f[n-1]-1));
	ans+=(a[1]-a[2]-d)%(f[n-1]-1);
	printf("%lld\n",ans);
}
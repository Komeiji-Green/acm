#include<bits/stdc++.h> 
#define inf 0x7fffffff
#define ll long long
#define oo 1000000000
using namespace std;
const int maxn=10000010;
long long n,k;
inline int read(){
    int f=1,x=0;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return f*x;
}
struct shai{
    int p[maxn],id1[maxn],id2[maxn],ncnt,m;
    ll g[maxn],sum[maxn],A[maxn],T,n;
    bool used[maxn];
    int Getid(ll x){
        return x<=T?id1[x]:id2[n/x];
    }
    void init(){
    	memset(used,0,sizeof(used));
    	ncnt=m=0;
        T=sqrt(n+0.5);
        for(int i=2;i<=T;i++){
            if(!used[i]){
            	p[++ncnt]=i;
				sum[ncnt]=sum[ncnt-1]+i;
			}
            for(int j=1;j<=ncnt&&i*p[j]<=T;j++){
                used[i*p[j]]=1;
                if(i%p[j]==0)break;
            }
        }
        for(ll l=1;l<=n;l=n/(n/l)+1){
            A[++m]=n/l;
            if(A[m]<=T)id1[A[m]]=m;
			else id2[n/A[m]]=m;
            g[m]=A[m]*(A[m]+1)/2+1;
        }
        for(int i=1;i<=ncnt;++i) 
            for(int j=1;j<=m&&(ll)p[i]*p[i]<=A[j];++j) 
                g[j]=g[j]-(ll)p[i]*(g[Getid(A[j]/p[i])]-sum[i-1]);
    }
    ll solve(ll x){
        if(x<=1)return x;
        else return n=x,init(),g[Getid(n)];
    }
}DD;
int main() {
	int T;
	scanf("%d",&T);
	while (T--){
		cin>>n>>k;
    	ll t=(k+1)/2;
    	ll ans=DD.solve(n+1)%k;
    	ans=(ans+1LL*(1LL*(n%k+3)*(n%k)%k)*t%k)%k;
    	ans=(ans-4+k)%k;
    	printf("%lld\n",ans);
	}
	return 0;
}
/*
4
3 998244353
100 998244353
1000000000 998244353
10000000000 998244353
*/
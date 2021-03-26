#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;
typedef long long ll;
const int maxn=100010;

struct tree{
	int L,R,v,m;
	int cnt,t1,t2;
}T[maxn<<2];

int TT,n,q;
int f[maxn*2];
char s[10];

void build(int o,int l,int r){
	T[o].L=l;T[o].R=r;
	T[o].v=0;T[o].m=r-l+1;
	T[o].cnt=T[o].t1=T[o].t2=0;
	if (l==r)return;
	int mid=l+r>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
}

void pushdown(int o){
	if (!T[o].cnt)return;
	int ls=o<<1,rs=ls|1;
	int cnt=T[o].cnt,t1=T[o].t1,t2=T[o].t2;
	
	//ls
	T[ls].v=((1ll*f[cnt]*T[ls].v%MOD+1ll*t1*(T[ls].R-T[ls].L+1)%MOD)%MOD+(1ll*f[cnt]*t2%MOD)*T[ls].m%MOD)%MOD;
	T[ls].m=1ll*f[2*cnt]*T[ls].m%MOD;
	T[ls].cnt+=cnt;
	T[ls].t1=(1ll*f[cnt]*T[ls].t1%MOD+t1)%MOD;
	T[ls].t2=(1ll*f[T[ls].cnt]*t2%MOD+t2)%MOD;
	//rs
	T[rs].v=((1ll*f[cnt]*T[rs].v%MOD+1ll*t1*(T[rs].R-T[rs].L+1)%MOD)%MOD+(1ll*f[cnt]*t2%MOD)*T[rs].m%MOD)%MOD;
	T[rs].m=1ll*f[2*cnt]*T[rs].m%MOD;
	T[rs].cnt+=cnt;
	T[rs].t1=(1ll*f[cnt]*T[rs].t1%MOD+t1)%MOD;
	T[rs].t2=(1ll*f[T[rs].cnt]*t2%MOD+t2)%MOD;
	//father
	T[o].cnt=T[o].t1=T[o].t2=0;
}

void update(int o,int l,int r,int d){
	if (l<=T[o].L&&T[o].R<=r){
		T[o].v=((10ll*T[o].v%MOD+1ll*(T[o].R-T[o].L+1)*d%MOD)%MOD+(10ll*d%MOD)*T[o].m%MOD)%MOD;
		T[o].m=100ll*T[o].m%MOD;
		++T[o].cnt;
		T[o].t1=(10ll*T[o].t1%MOD+d)%MOD;
		T[o].t2=(1ll*f[T[o].cnt-1]*d%MOD+T[o].t2)%MOD;
		return;
	}
	pushdown(o);
	int mid=T[o].L+T[o].R>>1;
	int ls=o<<1,rs=ls|1;
	if (l<=mid) update(ls,l,r,d);
	if (r>mid)  update(rs,l,r,d);
	T[o].v=(T[ls].v+T[rs].v)%MOD;
	T[o].m=(T[ls].m+T[rs].m)%MOD;
}

int query(int o,int l,int r){
	//printf("%d:%d %d\n",o,T[o].L,T[o].R);
	if (l<=T[o].L&&T[o].R<=r)return T[o].v;
	pushdown(o);
	int mid=T[o].L+T[o].R>>1,ans=0;
	if (l<=mid) ans+=query(o<<1,l,r);
	if (r>mid)  ans=(ans+query(o<<1|1,l,r))%MOD;
	return ans;
}

int main(){
	f[0]=1;
	for (int i=1;i<maxn*2;++i)f[i]=10ll*f[i-1]%MOD;
	scanf("%d",&TT);
	for (int o=1;o<=TT;++o){
		scanf("%d%d",&n,&q);
		printf("Case %d:\n",o);;
		build(1,1,n);
		int x,y,z;
		while (q--){
			scanf("%s",s+1);
			if (s[1]=='w'){
				scanf("%d%d%d",&x,&y,&z);
				update(1,x,y,z);
				//printf(" %d\n",T[1].v);
			}else{
				scanf("%d%d",&x,&y);
				printf("%d\n",query(1,x,y));
			}
		}
	}
}
#include<bits/stdc++.h>
#define M 1005
using namespace std;
int dp[M][70],ans1,ans2,ans3;
bool mark[300];
#define mod 998244353
void chk(int &a,int b){
	a+=b;
	if(a>=mod)a-=mod;
}
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int solve(int x){
	int ans=0;
	printf("%d\n",x);
	for(int i=0;i<64;i++){
		//枚举三位 
		memset(dp,0,sizeof(dp));
		dp[0][i]=1;
		for(int j=1;j<=x;j++){
			for(int k=0;k<64;k++){
				if(dp[j-1][k]){
					for(int q=0;q<4;q++){
						if(mark[k*4+q])continue;
						chk(dp[j][(k%16)*4+q],dp[j-1][k]);
					}
					//printf("有毒%d %d %d %d\n",j-1,k,dp[j-1][k],dp[j-1][k+1]);
				}
			}
		}
		for(int j=0;j<64;j++)chk(ans,dp[x][j]);
	}
	return ans;
}
int main(){
	int i,j,n,m,q,k,a,b,c,d,ans=0;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		scanf("%d %d %d %d",&a,&b,&c,&d);
		a=a*64+b*16+c*4+d;
		mark[a]=1;
	}
	for(i=1;i<=n;i++){
		printf("%d\n",solve(gcd(i,n)));
		chk(ans,solve(gcd(i,n)));
	}
	printf("%d\n",ans);
}
/*
4 3
0 1 2 3
1 2 3 1
2 1 3 0
*/
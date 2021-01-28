#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
 
const int N=255;
 
long double dp[N][N],P[N],D[N],ans;
int n,m,T;
 
long double Qpow(long double x,int y){
long double ans=1.0;
while(y){
    if(y&1)ans=ans*x;
    x*=x;
    y>>=1;
}
return ans;
}
 
int main(){
freopen("C.in","r",stdin);
freopen("C.out","w",stdout);
scanf("%d",&T);
while(T--){
    scanf("%d %d",&n,&m);
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++){
        double x,y;
        scanf("%lf %lf",&x,&y);
        P[i]=x;D[i]=y;
    }
    dp[0][m]=1.0;
    ans=0.0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=dp[i-1][j]*Qpow(1-P[i-1],j)+dp[i-1][j+1]*(1-Qpow(1-P[i-1],j+1));
            ans+=dp[i][j]*(1-Qpow(1-P[i],j))*D[i];
        }
    }
    printf("%.10lf\n",(double)ans);
}
return 0;
}
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int sum[105][5],f[105][105][15],a[105][5],n,m,K;

int main(){
freopen("G.in","r",stdin);
freopen("G.out","w",stdout);
scanf("%d %d %d",&n,&m,&K);
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        scanf("%d",&a[i][j]);
        sum[i][j]=sum[i-1][j]+a[i][j];
    }
}
memset(f,-127,sizeof(f));
if(m==1){
    for(int i=0;i<=n;i++)f[i][1][0]=0;
    for(int i=1;i<=n;i++){
        for(int k=1;k<=K;k++){
            f[i][1][k]=f[i-1][1][k];
            for(int j=0;j<i;j++){
                f[i][1][k]=max(f[i][1][k],f[j][1][k-1]+sum[i][1]-sum[j][1]);
            }
        }
    }
    printf("%d\n",f[n][1][K]);
}
else if(m==2){
    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)f[i][j][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=K;k++){
                f[i][j][k]=max(f[i-1][j][k],f[i][j-1][k]);
                for(int ix=0;ix<i;ix++)f[i][j][k]=max(f[i][j][k],f[ix][j][k-1]+sum[i][1]-sum[ix][1]);
                for(int jx=0;jx<j;jx++)f[i][j][k]=max(f[i][j][k],f[i][jx][k-1]+sum[j][2]-sum[jx][2]);
                if(i==j)for(int x=0;x<i;x++)f[i][j][k]=max(f[i][j][k],f[x][x][k-1]+sum[i][1]-sum[x][1]+sum[j][2]-sum[x][2]);
            }
        }
    }
    printf("%d\n",f[n][n][K]);
}
return 0;
}
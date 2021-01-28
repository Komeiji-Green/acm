#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
 
int n,en,h[5005],tx1[5005],tx2[5005],dep[5005],mx_dep;
long long ans=0;
 
struct Edge{
int b,next;
}e[10005];
 
void AddEdge(int sa,int sb){
e[++en].b=sb;
e[en].next=h[sa];
h[sa]=en;
}
 
void Dfs(int u,int fa,int deep){
mx_dep=max(mx_dep,deep);
dep[deep]++;
for(int i=h[u];i;i=e[i].next){
    int v=e[i].b;
    if(v!=fa)Dfs(v,u,deep+1);
}
}
 
int main(){
freopen("A.in","r",stdin);
freopen("A.out","w",stdout);
scanf("%d",&n);
for(int i=1;i<n;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    AddEdge(x,y);AddEdge(y,x);
}
for(int i=1;i<=n;i++){
    memset(tx1,0,sizeof(tx1));
    memset(tx2,0,sizeof(tx2));
    for(int j=h[i];j;j=e[j].next){
        memset(dep,0,sizeof(dep));
        int v=e[j].b;
        Dfs(v,i,1);
        for(int k=1;k<=mx_dep;k++){
            ans+=tx2[k]*dep[k];
            tx2[k]+=dep[k]*tx1[k];
            tx1[k]+=dep[k];
        }
    }
}
printf("%lld\n",ans);
return 0;
}
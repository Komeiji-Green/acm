#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int N=2000005;

int c[N],n,m,ans;
vector<int> V[N];

int cmp(int x,int y){
return c[x]<c[y];
}

void dfs(int u){
for(unsigned int i=0;i<V[u].size();i++){
    dfs(V[u][i]);
}
sort(V[u].begin(),V[u].end(),cmp);
for(unsigned int i=0;i<V[u].size();i++){
    if(c[u]+c[V[u][i]]-1<=m){
        c[u]+=c[V[u][i]]-1;
        ans++;
    }
    else break;
}
}

int main(){
//freopen("E.in","r",stdin);
//freopen("E.out","w",stdout);
scanf("%d %d",&n,&m);
for(register int i=0;i<n;i++){
    scanf("%d",&c[i]);
}
for(register int i=0;i<n;i++){
    int tn,sn;
    scanf("%d",&tn);
    c[i]+=tn;
    for(register int j=1;j<=tn;j++){
        scanf("%d",&sn);
        V[i].push_back(sn);
    }
}
dfs(0);
printf("%d\n",ans);
return 0;
}

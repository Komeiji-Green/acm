#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
  
const int N=3005;
const double Pi=acos(-1);
  
int n,Top,cnt[2][3],test[N];
long long ans;
  
struct Point{
int x,y;
Point(){}
Point(int sa,int sb){x=sa;y=sb;}
friend Point operator+(Point A,Point B){return Point(A.x+B.x,A.y+B.y);}
friend Point operator-(Point A,Point B){return Point(A.x-B.x,A.y-B.y);}
}O;
  
double Atan(Point A){double x=atan2(A.y,A.x);return x>0?x:x+Pi;}
  
pair<Point,int> poi[N],St[N],St2[N];
pair<double,int> Stab[N];
  
void Cal(int col){
memset(cnt,0,sizeof(cnt));
for(int i=1;i<=Top;i++)Stab[i]=make_pair(Atan(St[i].first-O),i);
sort(Stab+1,Stab+Top+1);
for(int i=1;i<=Top;i++)St2[i]=St[Stab[i].second];
for(int i=1;i<=Top;i++)St[i]=St2[i];
for(int i=1;i<=Top;i++){
    if(St[i].first.y<O.y || St[i].first.y==O.y && St[i].first.x>O.x)cnt[test[i]=0][St[i].second]++;
    else cnt[test[i]=1][St[i].second]++;
}
for(int i=1;i<=Top;i++){
    cnt[test[i]][St[i].second]--;
    int CanDoneFirst=1,CanDoneSecond=1;
    if(col!=0)CanDoneFirst*=cnt[0][0];
    if(col!=1)CanDoneFirst*=cnt[0][1];
    if(col!=2)CanDoneFirst*=cnt[0][2];
    if(St[i].second!=0)CanDoneSecond*=cnt[1][0];
    if(St[i].second!=1)CanDoneSecond*=cnt[1][1];
    if(St[i].second!=2)CanDoneSecond*=cnt[1][2];
    ans+=(long long)CanDoneFirst*CanDoneSecond;
    CanDoneFirst=1,CanDoneSecond=1;
    if(col!=0)CanDoneFirst*=cnt[1][0];
    if(col!=1)CanDoneFirst*=cnt[1][1];
    if(col!=2)CanDoneFirst*=cnt[1][2];
    if(St[i].second!=0)CanDoneSecond*=cnt[0][0];
    if(St[i].second!=1)CanDoneSecond*=cnt[0][1];
    if(St[i].second!=2)CanDoneSecond*=cnt[0][2];
    ans+=(long long)CanDoneFirst*CanDoneSecond;
    cnt[test[i]^=1][St[i].second]++;
}
}
  
int main(){
freopen("F.in","r",stdin);
freopen("F.out","w",stdout);
scanf("%d",&n);
for(int i=1;i<=n;i++){
    scanf("%d %d %d",&poi[i].first.x,&poi[i].first.y,&poi[i].second);
}
for(int i=1;i<=n;i++){
    Top=0;
    for(int j=1;j<=n;j++)if(i!=j)St[++Top]=poi[j];
    O=poi[i].first;
    Cal(poi[i].second);
}
printf("%lld\n",ans/4);
return 0;
}
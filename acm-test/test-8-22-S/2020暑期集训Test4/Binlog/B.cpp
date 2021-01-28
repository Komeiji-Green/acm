#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
 
const int N=4005;
const double eps=1e-17;
 
int n,cnt,ind[N];
double ans;
 
struct Point{
long long x,y;
int id;
Point(){}
Point(long long _x,long long _y){x=_x;y=_y;}
friend inline Point operator+(const Point &A,const Point &B){return Point(A.x+B.x,A.y+B.y);}
friend inline Point operator-(const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
friend inline long long operator*(const Point &A,const Point &B){return A.x*B.y-A.y*B.x;}
friend inline bool operator==(const Point &A,const Point &B){return A.x==B.x && A.y==B.y;}
}ChosenPoint,point[N<<1];
 
inline int Check(Point A){
if(A.x-ChosenPoint.x>0 && A.y-ChosenPoint.y>=0)return 0;
if(A.x-ChosenPoint.x<=0 && A.y-ChosenPoint.y>0)return 1;
if(A.x-ChosenPoint.x<0 && A.y-ChosenPoint.y<=0)return 2;
return 3;
}
 
inline int Dist2(const Point &A,const Point &B){return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);}
inline bool cmp(const Point &A,const Point &B){int x=Check(A),y=Check(B);if(x!=y)return x<y;return (A-ChosenPoint)*(B-ChosenPoint)>=0;}
inline bool OnRight(const Point &A,const Point &B,const Point &C){return (B-A)*(C-A)>=0;}
 
struct Pair_Points{
Point A,B;
}poi[N];
 
int main(){
freopen("B.in","r",stdin);
freopen("B.out","w",stdout);
scanf("%d",&n);
if(n<3){puts("0.000000");return 0;}
for(int i=1;i<=n;i++)scanf("%lld %lld %lld %lld",&poi[i].A.x,&poi[i].A.y,&poi[i].B.x,&poi[i].B.y);
for(int i=1;i<=n;i++){
    ChosenPoint=poi[i].A;
    cnt=0;
    for(int j=1;j<=n;j++){
        if(i==j)continue;
        point[++cnt]=poi[j].A;point[cnt].id=j;point[++cnt]=poi[j].B;point[cnt].id=j;
    }
    sort(point+1,point+cnt+1,cmp);
    memset(ind,0,sizeof(ind));
    int cntx[3]={n-1},pos=1;
    for(int j=cnt+1;j<=2*cnt;j++)point[j]=point[j-cnt];
    for(int j=1;j<=cnt;j++){
        while(pos<j+cnt && OnRight(ChosenPoint,point[j],point[pos])){
            ind[point[pos].id]++;
            cntx[ind[point[pos].id]]++;
            cntx[ind[point[pos].id]-1]--;
            pos++;
        }
        //printf("%d %d %d %d\n", pos, cntx[0], cntx[1], cntx[2]);
        if(cntx[1]+cntx[2]==n-1){
            double afk=0.125;
            if(ind[point[j].id]==1)afk/=pow(2,cntx[1]-1);
            else afk/=pow(2,cntx[1]);
            ans+=afk*(ChosenPoint*point[j]);
        }
        ind[point[j].id]--;
        cntx[ind[point[j].id]]++;
        cntx[ind[point[j].id]+1]--;
    }
}
for(int i=1;i<=n;i++){
    ChosenPoint=poi[i].B;
    cnt=0;
    for(int j=1;j<=n;j++){
        if(i==j)continue;
        point[++cnt]=poi[j].A;point[cnt].id=j;point[++cnt]=poi[j].B;point[cnt].id=j;
    }
    sort(point+1,point+cnt+1,cmp);
    memset(ind,0,sizeof(ind));
    int cntx[3]={n-1},pos=1;
    for(int j=cnt+1;j<=2*cnt;j++)point[j]=point[j-cnt];
    for(int j=1;j<=cnt;j++){
        while(pos<j+cnt && OnRight(ChosenPoint,point[j],point[pos])){
            ind[point[pos].id]++;
            cntx[ind[point[pos].id]]++;
            cntx[ind[point[pos].id]-1]--;
            pos++;
        }
        //printf("%d %d %d %d\n", pos, cntx[0], cntx[1], cntx[2]);
        if(cntx[1]+cntx[2]==n-1){
            double afk=0.125;
            if(ind[point[j].id]==1)afk/=pow(2,cntx[1]-1);
            else afk/=pow(2,cntx[1]);
            ans+=afk*(ChosenPoint*point[j]);
        }
        ind[point[j].id]--;
        cntx[ind[point[j].id]]++;
        cntx[ind[point[j].id]+1]--;
    }
}
printf("%.17lf\n",ans);
return 0;
}
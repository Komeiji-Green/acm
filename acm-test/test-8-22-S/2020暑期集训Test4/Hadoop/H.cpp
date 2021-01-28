#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=100005,M=15;
const long long P=1000000003ll,base=233ll;

bool f[M][N];
int n,len,pos[M],cnt;
long long Px[N]={1},ha1[N],ha2[N];
char s[N],str[N];

long long H1(int st,int ed){
if(st>ed)return 0ll;
return ((ha1[ed]-ha1[st-1]*Px[ed-st+1])%P+P)%P;
}

long long H2(int st,int ed){
if(st>ed)return 0ll;
return ((ha2[ed]-ha2[st-1]*Px[ed-st+1])%P+P)%P;
}

int main(){
freopen("H.in","r",stdin);
freopen("H.out","w",stdout);
scanf("%s",str+1);
len=strlen(str+1);
str[++len]='?';
for(int i=1;i<=len;i++)if(str[i]<'a' || str[i]>'z')pos[++cnt]=i;
for(int i=1;i<=len;i++)ha1[i]=ha1[i-1]*base%P+str[i];
for(int i=1;i<=100000;i++)Px[i]=Px[i-1]*base%P;
scanf("%d",&n);
while(n--){
    scanf("%s",s+1);
    len=strlen(s+1);
    s[++len]='#';
    for(int i=1;i<=len;i++)ha2[i]=ha2[i-1]*base%P+s[i];
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=0;i<cnt;i++){
        if(str[pos[i]]=='*')for(int j=1;j<=len;j++)if(f[i][j-1])f[i][j]=1;
        for(int j=0;j<=len;j++){
            //printf("Ha1[%d,%d]=%lld , Ha2[%d,%d]=%lld\n",pos[i]+1,pos[i+1]-1,H1(pos[i]+1,pos[i+1]-1),j+1,j+pos[i+1]-pos[i]-1,H2(j+1,j+pos[i+1]-pos[i]-1));
            if(f[i][j]&&H1(pos[i]+1,pos[i+1]-1)==H2(j+1,j+pos[i+1]-pos[i]-1)){
                if(str[pos[i+1]]=='?')f[i+1][j+pos[i+1]-pos[i]]=1;
                else f[i+1][j+pos[i+1]-pos[i]-1]=1;
            }
        }
    }
    puts(f[cnt][len]?"YES":"NO");
}
return 0;
}
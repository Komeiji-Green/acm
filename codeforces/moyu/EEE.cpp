#include<bits/stdc++.h> 
#define inf 0x7fffffff
#define ll long long
using namespace std;
const int maxn=1000010;
char str[maxn];
int A[10],edx,edy,T;
char ans[maxn];
int main(){
	int i,j,n,nowx,nowy;
	cin>>T;
	while(T--){
		int len=0;scanf("%d %d",&edx,&edy);
		scanf("%s",str);
		n=strlen(str);
		memset(A,0,sizeof(A)); 
		
		if(edx==0&&edy==0){
			puts("Impossible");
			continue;
		}
		for(i=0;i<n;i++){
			if(str[i]=='U')A[1]++;
			else if(str[i]=='D')A[2]++;
			else if(str[i]=='L')A[3]++;
			else A[4]++;
		}//puts("!");
		//printf("%d %d %d %d\n",A[1],A[2],A[3],A[4]);
		if(A[1]-A[2]==edy&&A[4]-A[3]==edx){
			puts("Impossible");
			continue;
		}
		
		if(edx==0&&edy>0){
			if(A[3]==0&&A[4]==0){
				if(A[1]-A[2]>=edy){
					puts("Impossible");
					continue;
				}
			}
		}
		if(edx==0&&edy<0){
			if(A[3]==0&&A[4]==0){
				if(A[2]-A[1]>=-edy){
					puts("Impossible");
					continue;
				}
			}
		}
		if(edy==0&&edx>0){
			if(A[1]==0&&A[2]==0){
				if(A[4]-A[3]>=edx){
					puts("Impossible");
					continue;
				}
			}
		}
		if(edy==0&&edx<0){
			if(A[1]==0&&A[2]==0){
				if(A[3]-A[4]>=-edx){
					puts("Impossible");
					continue;
				}
			}
		}
		//puts("!");
		if(edx>=0&&edy>=0){
			nowx=-A[3];
			for(j=1;j<=A[3];j++)ans[len++]='L';
			nowy=-A[2];
			for(j=1;j<=A[2];j++)ans[len++]='D';
			if(A[1]!=edy-nowy){
				for(j=1;j<=A[1];j++)ans[len++]='U';
				for(j=1;j<=A[4];j++)ans[len++]='R';
			}
			else if(A[4]!=edx-nowx){
				for(j=1;j<=A[4];j++)ans[len++]='R';
				for(j=1;j<=A[1];j++)ans[len++]='U';
			}else {
				puts("Impossible");
				continue;
			}
		}
		else if(edx<=0&&edy>=0){
			nowx=A[4];
			nowy=-A[2];
			for(j=1;j<=A[4];j++)ans[len++]='R';
			for(j=1;j<=A[2];j++)ans[len++]='D';
			if(A[1]!=edy-nowy){
				for(j=1;j<=A[1];j++)ans[len++]='U';
				for(j=1;j<=A[3];j++)ans[len++]='L';
			}else if(A[3]!=nowx-edx){
				for(j=1;j<=A[3];j++)ans[len++]='L';
				for(j=1;j<=A[1];j++)ans[len++]='U';
			}else {
				puts("Impossible");
				continue;
			}
		}else if(edx<=0&&edy<=0){
			nowx=A[4];
			nowy=A[1];
			for(j=1;j<=A[4];j++)ans[len++]='R';
			for(j=1;j<=A[1];j++)ans[len++]='U';
			if(A[2]!=nowy-edy){
				for(j=1;j<=A[2];j++)ans[len++]='D';
				for(j=1;j<=A[3];j++)ans[len++]='L';
			}else if(A[3]!=nowx-edx){
				for(j=1;j<=A[3];j++)ans[len++]='L';
				for(j=1;j<=A[2];j++)ans[len++]='D';
			}else {
				puts("Impossible");
				continue;
			}
		}else {
			nowx=-A[3];
			nowy=A[1];
			for(j=1;j<=A[3];j++)ans[len++]='L';
			for(j=1;j<=A[1];j++)ans[len++]='U';
			if(A[2]!=nowy-edy){
				for(j=1;j<=A[2];j++)ans[len++]='D';
				for(j=1;j<=A[4];j++)ans[len++]='R';
			}else if(A[4]!=edx-nowx){
				for(j=1;j<=A[4];j++)ans[len++]='R';
				for(j=1;j<=A[2];j++)ans[len++]='D';
			}else {
				puts("Impossible");
				continue;
			}
		}
		for(int i=0;i<len;i++){
			printf("%c",ans[i]);
		}
		puts("");
	} 
	return 0;
} 

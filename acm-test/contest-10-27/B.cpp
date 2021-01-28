#include<bits/stdc++.h>
#define ll long long
#define inf 0x7fffffff
using namespace std;
const int maxn=200010;
inline int read(){
	int f=1,x=0;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return f*x;
}

struct point{
	int x,y;
}P[maxn];

int n,m,k,Q;
int fx[]={-1,0,1,0};
int fy[]={0,1,0,-1};
int f[200][maxn];
bool vis[maxn];
queue<pair<int,int>> q;

void BFS(int o,int sx,int sy){
	//printf(" %d %d %d\n",o,sx,sy);
	for (int i=1;i<=n*m;++i)f[o][i]=-1;
	f[o][(sx-1)*m+sy]=0;
	//printf("%d\n",(sx-1)*m+sy);
	q.push(make_pair(sx,sy));
	while (!q.empty()){
		pair<int,int> u=q.front();
		q.pop();
		for (int i=0;i<4;++i){
			pair<int,int> v;
			v.first=u.first+fx[i];
			v.second=u.second+fy[i];
			if (v.first<1||v.first>n||v.second<1||v.second>n)continue;
			if (vis[(v.first-1)*m+v.second])continue;
			if (f[o][(v.first-1)*m+v.second]!=-1)continue;
			f[o][(v.first-1)*m+v.second]=f[o][(u.first-1)*m+u.second]+1;
			q.push(v);
		}
	}
}

int main(){
	memset(vis,0,sizeof(vis));
	n=read();m=read();k=read();Q=read();
	for (int i=1;i<=k;++i){
		P[i].x=read();P[i].y=read();
		vis[(P[i].x-1)*m+P[i].y]=1;
	}
	for (int i=1;i<=k;++i){
		int x,y;
		for (int j=0;j<4;++j){
			x=P[i].x+fx[j];
			y=P[i].y+fy[j];
			if (x<1||x>n||y<1||y>n)continue;
			if (vis[(x-1)*m+y])continue;
			BFS(4*(i-1)+j+1,x,y);
		}
	}
	int sx,sy,tx,ty;
	int lx,ly,rx,ry;
	while (Q--){
		sx=read();sy=read();tx=read();ty=read();
		lx=min(sx,tx);ly=min(sy,ty);
		rx=max(sx,tx);ry=max(sy,ty);
		bool b=0;
		int ans=inf;
		for (int i=1;i<=k;++i)
			if (lx<=P[i].x&&P[i].x<=rx&&ly<=P[i].y&&P[i].y<=ry){
				b=1;
				for (int j=0;j<4;++j){
					int x,y;
					x=P[i].x+fx[j];
					y=P[i].y+fy[j];
					if (x<1||x>n||y<1||y>n)continue;
					if (vis[(x-1)*m+y])continue;
					int o=4*(i-1)+j+1;
					if (f[o][(sx-1)*m+sy]==-1||f[o][(tx-1)*m+ty]==-1)continue;
					ans=min(ans,f[o][(sx-1)*m+sy]+f[o][(tx-1)*m+ty]);
				}
			}
		if (!b)ans=rx-lx+ry-ly;
		if (b&&ans==inf)ans=-1;
		printf("%d\n",ans);
	}
}

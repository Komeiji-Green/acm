#include<bits/stdc++.h>
using namespace std;

// 带花树模板
const int maxn=505;

struct Match {
    int n,father[maxn],vst[maxn],match[maxn],pre[maxn],Type[maxn],times;
    vector<int>edges[maxn];
    queue<int>Q;

    void ine(int x,int y) { edges[x].push_back(y); }
    void ine2(int x, int y) { ine(x, y); ine(y, x); } 

    void init(int num) {
        times=0;
        n = num;
        for(int i = 0; i <= n; ++i) edges[i].clear(),vst[i]=0,match[i]=0,pre[i]=0;
    }

    int LCA(int x,int y) {
        times++;
        x=father[x],y=father[y]; //已知环位置
        while(vst[x]!=times) {
            if(x) {
                vst[x]=times;
                x=father[pre[match[x]]];
            }
            swap(x,y);
        }
        return x;
    }

    void blossom(int x,int y,int lca) {
        while(father[x]!=lca) {
            pre[x]=y;
            y=match[x];
            if(Type[y]==1) {
                Type[y]=0;
                Q.push(y);
            }
            father[x]=father[y]=father[lca];
            x=pre[y];
        }
    }

    int Augument(int s) {
        for(int i=0; i<=n; ++i)father[i]=i,Type[i]=-1;
        Q=queue<int>();
        Type[s]=0;
        Q.push(s); //仅入队o型点
        while(!Q.empty()) {
            int Now=Q.front();
            Q.pop();
            for(int Next:edges[Now]) {
                if(Type[Next]==-1) {
                    pre[Next]=Now;
                    Type[Next]=1; //标记为i型点
                    if(!match[Next]) {
                        for(int to=Next,from=Now; to; from=pre[to]) {
                            match[to]=from;
                            swap(match[from],to);
                        }
                        return true;
                    }
                    Type[match[Next]]=0;
                    Q.push(match[Next]);
                } else if(Type[Next]==0&&father[Now]!=father[Next]) {
                    int lca=LCA(Now,Next);
                    blossom(Now,Next,lca);
                    blossom(Next,Now,lca);
                }
            }
        }
        return false;
    }

    int gao() {
        int res = 0;
        for(int i = n; i >= 1; --i) if(!match[i]) res += Augument(i);
        return res;
    }
} G;

char a[505][505];

int main() {
    int T, n, m;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int i = 1; i <= n; ++i) {
            scanf("%s", a[i] + 1);
        }
        int num = 2 * n + m;
        G.init(num);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(a[i][j]=='1') G.ine2(i, 2 * n + j), G.ine2(n + i, 2 * n + j);
            }
        }
        for(int i = 1; i <= n; ++i) G.ine2(i, i + n);
        int ans = G.gao();
        printf("%d\n",ans-n);
    }
	return 0;
}
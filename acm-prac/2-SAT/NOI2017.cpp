#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
const int N = 233333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


int clc, low[N], dfn[N];
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
void tarjan(int cur, int dad)
{
    sta[++top] = cur;
    vis[cur] = 0;
    dfn[cur] = ++clc;
    low[cur] = clc;
    //bool flag = false;
    reg(i, cur)
    {
        //flag = true;
        int nex = e[i].to;
        if (!dfn[nex]) { // ����
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        }
        else if (!vis[nex]) { // ���ر�
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if((dfn[cur] == low[cur]) /*|| (dad == 0 && !flag)*/) { 
        sccnum++;
        do {
            vis[sta[top]] = 1;
            scc[sta[top]] = sccnum;
        } while(top && sta[top--] != cur);
    }
}

char s[N];
int id[N][4], num = 0;
int main() {
	int n, m, d;
    cin >> n >> d;
    scanf("%s", s + 1);
    for(int i = 1; i <= n; ++i) {
        if(s[i] == 'x') {
            for(int j = 1; j <= 3; ++j) id[i][j] = n + num + j;
            for(int j = 1; j <= 3; ++j) {
                for(int k = 1; k <= 3; ++k) {
                    if(k == j) continue;
                    ine(id[i][j]<<1|1, id[i][k]<<1);
                }
            }
            num += 3;
        }
    }
    cin >> m;
    int i, j, u, v;
    char aa[4], bb[4];
    while(m--) {
        scanf("%d %s %d %s", &i, aa, &j, bb);
        if(s[i] == 'x') {
            u = (id[i][aa[0]-'A'+1]<<1|1);
        } else {
            char c = s[i], cc = aa[0];
            if(c-'a' == cc-'A') u = 0;
            else {
                if(c == 'a') {
                    u = cc == 'B' ? 
                }
            }
        }
    }

}

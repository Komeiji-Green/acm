#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 407;
int w[N][N], li[N][N], inq[N];
bool vis[N*N];

char s[4000050];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, m, q, x, y, sz, val, cnt;
        cin >> n >> m >> q;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                scanf("%d", &w[i][j]);
            }
        }
        queue<int> q1, q2;
        while(q--) {
            scanf("%d %d", &x, &y);
            scanf("%s", s);
            for(int i=0; s[i]; ++i) {
                if(s[i]=='U') {
                    ++y;
                    li[y][++li[y][0]]=x; if(!inq[y]) q1.push(y), inq[y]=1;
                } else if(s[i] == 'D') {
                    li[y][++li[y][0]]=x; if(!inq[y]) q1.push(y), inq[y]=1;
                    --y;
                } else if(s[i] == 'L') {
                    --x;
                } else if(s[i] == 'R') {
                    ++x;
                }
            }
            cnt = 0;
            while(!q1.empty()) {
                y=q1.front(); q1.pop();
                sz = li[y][0];
                sort(li[y] + 1, li[y] + sz + 1);
                for(int i = 2; i <= sz; i += 2) {
                    for(x = li[y][i-1]+1; x <= li[y][i]; ++x) {
                        val = w[x][y];
                        if(!vis[val]) vis[val]=1, q2.push(val), ++cnt;
                    }
                }
                li[y][0]=0; inq[y]=0;
            }
            while(!q2.empty()) {
                vis[q2.front()]=0; q2.pop();
            }
            printf("%d\n", cnt);
        }
    }
}
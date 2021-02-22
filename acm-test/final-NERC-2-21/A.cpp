#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int a, b;
int stk[10]; // 1: a稳、2：b稳，3: a贴，4: b贴
int cx[2][6] = {
    {-1, 25, 0, 25, 23},
    {-1, 15, 0, 15, 13}
}, cy[2][6] = {
    {-1, 0, 25, 23, 25},
    {-1, 0, 15, 13, 15}
}, ux[2][6] = {
    {-1, 0, 23, 0, 0},
    {-1, 0, 13, 0, 0}
}, uy[2][6] = {
    {-1, 23, 0, 0, 0},
    {-1, 13, 0, 0, 0}
};
int ox[6], oy[6], ansx, ansy;
bool f = 0;


void chk(int n) {
    int x = a, y = b;
    int j = 0; // 自由项
    int sx[6] = {}, sy[6] = {}, wx = 0, wy = 0;
    int ed = 0;
    for(int i = 1; i <= n; ++i) {
        int c = stk[i];
        if(c >= 3) j = i;
        if(c == 1 || c == 3) ++wx;
        else ++wy;
        if(!ed && (wx == 3 || wy == 3)) ed = i;
        sx[i] += cx[i==5][c];
        x -= cx[i==5][c];
        sy[i] += cy[i==5][c];
        y -= cy[i==5][c];
    }
    if(!ed || ed < n) return;
    if(x < 0 || y < 0) return;
    int mm = min(x, y);
    if(j) {
        sx[j] += mm; sy[j] += mm;
        x -= mm; y -= mm;
    }
    for(int i = 1; i <= n; ++i) {
        int c = stk[i];
        int d = min(ux[i==5][c], x);
        x -= d; sx[i] += d;
        d = min(uy[i==5][c], y);
        y -= d; sy[i] += d;
    }
    if(x || y) return;
    if(!f || wx - wy > ansx - ansy) {
        ansx = wx; ansy = wy; f = 1;
        for(int i = 1; i <= n; ++i) ox[i] = sx[i], oy[i] = sy[i];
    } 
}
void dfs(int cur) {
    chk(cur-1);
    if(cur > 5) return;
    for(int i = 1; i <= 4; ++i) {
        stk[cur] = i;
        dfs(cur + 1);
    }
}
int main() {
    int T; cin >> T;
    while(T--) {
        scanf("%d %d", &a, &b);
        ansx = ansy = 0; f = 0;
        dfs(1);
        if(!f) printf("Impossible\n");
        else {
            printf("%d:%d\n", ansx, ansy);
            int m = ansx + ansy;
            for(int i = 1; i <= m; ++i) {
                printf("%d:%d ", ox[i], oy[i]);
            }
            printf("\n");
        }
    }
}
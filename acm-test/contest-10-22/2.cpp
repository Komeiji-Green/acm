#include<bits/stdc++.h>
#include<vector>
#define rint register int
using namespace std;

const int N = 1005;

int n, m;
bool a[N][N], l[N][N][4]; // 00：左 01：右 10：上 11：下 false: 干 true: 湿

void pre() {
    for(int i = 0; i <= (n + 1); ++i) {
        a[i][0] = a[i][m + 1] = false;
        l[i][0][0] = l[i][0][1] = 0;
        l[i][0][2] = l[i][0][3] = i;
        l[i][m + 1][0] = l[i][m + 1][1] = m + 1;
        l[i][m + 1][2] = l[i][m + 1][3] = i;
    }
    for(int j = 0; j <= (m + 1); ++j) {
        a[0][j] = a[n + 1][j] = false;
        l[0][j][0] = l[0][j][1] = j;
        l[0][j][2] = l[0][j][3] = 0;
        l[n + 1][j][0] = l[n + 1][j][1] = j;
        l[n + 1][j][2] = l[n + 1][j][3] = n + 1;
    }
}

void change(int r, int c) {
    if(a[r][c]) { // 有效->无效
        for(int j = c; a[r][j]; ++j) l[r][j][0] = c;
        for(int j = c; a[r][j]; --j) l[r][j][1] = c;
        for(int i = r; a[i][c]; ++i) l[i][c][2] = r;
        for(int i = r; a[i][c]; --i) l[i][c][3] = r;
        a[r][c] = !a[r][c];
    } else {    // 无效->有效
        a[r][c] = !a[r][c];
        for(int j = c; a[r][j]; ++j) l[r][j][0] = l[r][c - 1][0];
        for(int j = c; a[r][j]; --j) l[r][j][1] = l[r][c + 1][1];
        for(int i = r; a[i][c]; ++i) l[i][c][2] = l[r - 1][c][2];
        for(int i = r; a[i][c]; --i) l[i][c][3] = l[r + 1][c][3];
    }
}



int gao(int x, int y) {
    vector<pair<int, int> > p;

    
}


char s[N];
int main() {
    int T;
    cin >> T;
    int q, op, x, y, res;
    while(T--) {
        scanf("%d %d %d", &n, &m, &q);
        for(int i = 1; i <= n; ++i) {
            scanf("%s", s + 1);
            for(int j = 1; j <= m; ++j) {
                a[i][j] = (s[j] != '#');
            }
        }
        pre();
        while(q--) {
            scanf("%d %d %d", &op, &x, &y);
            if(op == 1) {
                change(x, y);
            } else {
                res = gao(x, y);
            }
        }
    }
}
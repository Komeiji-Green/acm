#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
char s[maxn][maxn];
int a[maxn][maxn], b[3][3];

struct DD {
    DD(int _i, int _j, int _c, int _d, int _e, int _f) {
        i = _i, j=_j, c=_c, d=_d, e=_e,f=_f;
    }
    DD() {}
    int i, j, c, d, e, f;
    void show() {
        printf("%d %d %d %d %d %d\n", i, j, c, d, e, f);
    }
} ans[maxn*maxn];
int num = 0;
void gao(int i, int j, int c, int d, int e, int f) {
    ans[++num] = DD(i, j, c, d, e, f);
    a[i][j]^=1;
    a[c][d]^=1;
    a[e][f]^=1;
}

void uu(int x) {
    if(x == 1) {
        gao(1, 1, 1, 2, 2, 1);
    } else if(x == 2) {
        gao(1, 1, 1, 2, 2, 2);
    } else if(x == 3) {
        gao(1, 1, 2, 1, 2, 2);
    } else {
        gao(1, 2, 2, 1, 2, 2);
    }
}

void bdq(int x) {
    switch(x) {
        case 0:
        break;
        case 1:
        uu(1);uu(2);uu(3); break;
        case 2:
        uu(1);uu(2);uu(4); break;
        case 4:
        uu(1);uu(3);uu(4); break;
        case 8:
        uu(2);uu(3);uu(4); break;
        case 3:
        uu(3);uu(4); break;
        case 5:
        uu(2);uu(4); break;
        case 9:
        uu(1);uu(4); break;
        case 6:
        uu(2);uu(3); break;
        case 10:
        uu(1);uu(3); break;
        case 12:
        uu(1);uu(2); break;
        case 7:
        uu(1); break;
        case 11:
        uu(2); break;
        case 13:
        uu(3); break;
        case 14:
        uu(4); break;
        case 15:
        uu(1); uu(2); uu(3); uu(4); break;
        default:
        break;
    }
}

int main() {
    int T;
    cin >> T;

    /*
    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 4; ++j) {
            if((1<<j)&i) a[j/2 + 1][j%2 + 1] = 1;
            else a[j/2 + 1][j%2 + 1] = 0;
        }
        for(int j = 1; j <= 2; ++j) for(int k = 1; k <= 2; ++k) b[j][k] = a[j][k];
        for(int j = 0; j < 4; ++j) {
            for()
        }
    }*/

    while(T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        num = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%s", s[i] + 1);
        }
        for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) {
            a[i][j] = s[i][j] - '0';
        }
        for(int i = n; i > 2; --i) {
            for(int j = 1; j < m; ++j) {
                if(a[i][j]) {
                    gao(i, j, i - 1, j, i, j + 1);
                }
            }
            if(a[i][m]) gao(i, m, i - 1, m, i - 1, m - 1);
        }
        for(int j = m; j > 2; --j) {
            if(a[1][j]) gao(1, j, 1, j - 1, 2, j);
            if(a[2][j]) gao(2, j, 2, j - 1, 1, j - 1);
        }
        bdq(a[1][1]+(a[1][2]<<1)+(a[2][1]<<2)+(a[2][2]<<3));
        printf("%d\n", num);
        for(int i = 1; i <= num; ++i) ans[i].show();
    }
}
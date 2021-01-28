#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 1050;
const int INF = 0x3f3f3f3f;

int mm[N];
int maxv[N][N][25];
int minv[N][N][25];
int a[N][N];
void initrmq(int m, int n, int d) {
    mm[0] = -1;
    for(int i = 1; i <= d; i++) {
        if(i & (i - 1)) mm[i] = mm[i - 1];
        else mm[i] = mm[i - 1] + 1;
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            minv[i][j][0] = maxv[i][j][0] = a[i][j];
        }
    }

    for(int k = 1; k <= 12; k++) {
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if((i + (1 << k)) > (n + 1) || (i + (1 << k)) > (m + 1)) break;
                int dd = (1 << (k - 1));
                int lu = minv[i][j][k - 1];
                int ld = minv[i + dd][j][k - 1];
                int ru = minv[i][j + dd][k - 1];
                int rd = minv[i + dd][j + dd][k - 1];
                minv[i][j][k] = min(min(lu, ld), min(ru, rd));
                lu = maxv[i][j][k - 1];
                ld = maxv[i + dd][j][k - 1];
                ru = maxv[i][j + dd][k - 1];
                rd = maxv[i + dd][j + dd][k - 1];
                maxv[i][j][k] = max(max(lu, ld), max(ru, rd));
            }
        }
    }
}

int rmq(int i, int j, int d) {
    int k = mm[d];
    int dd = (1 << k);
    int lu = maxv[i][j][k];
    int ld = maxv[i + d - dd][j][k];
    int ru = maxv[i][j + d - dd][k];
    int rd = maxv[i + d - dd][j + d - dd][k];
    int mmax = max(max(lu, ld), max(ru, rd));
    lu = minv[i][j][k];
    ld = minv[i + d - dd][j][k];
    ru = minv[i][j + d - dd][k];
    rd = minv[i + d - dd][j + d - dd][k];
    int mmin = min(min(lu, ld), min(ru, rd));
    return mmax - mmin;
}

int main()
{
    int m, n, k;
    cin >> m >> n >> k;
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    initrmq(m, n, k);
    int ans = INF;
    for(int i = 1; i <= (n - k + 1); i++) {
        for(int j = 1; j <= (m - k + 1); j++) {
            ans = min(ans, rmq(i, j, k));
        }
    }
    printf("%d\n", ans);
}
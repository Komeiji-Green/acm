#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int f[16][2][2], mt[81][2][2], ans[16][3];

int chk(int x) {
    return mt[x][0][0] * mt[x][1][1] - mt[x][0][1] * mt[x][1][0];   
}
int main() {
    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 4; ++j) {
            f[i][j/2][j%2]= ((1<<j) & i) ? 1 : 0;
        }
    }
    int tot = 0;
    for(int a = -1; a <= 1; ++a) 
        for(int b = -1; b <= 1; ++b)
            for(int c = -1; c <= 1; ++c)
                for(int d = -1; d <= 1; ++d) {
                    mt[tot][0][0] = a;
                    mt[tot][0][1] = b;
                    mt[tot][1][0] = c;
                    mt[tot][1][1] = d;
                    ++tot;
                }
    for(int i = 0; i < 16; ++i) { 
        bool ok = 0;
        for(int a = 0; a < 81 && !ok; ++a)
        for(int b = 0; b < 81 && !ok; ++b)
        for(int c = 0; c < 81 && !ok; ++c) {
            if(!chk(c)) continue;
            ok = 1;
            for(int j = 0; j <= 1; ++j)
            for(int k = 0; k <= 1; ++k) {
                for(int s = 0; s <= 1; ++s) {
                    if(mt[a][s][j] * mt[b][s][k] != mt[c][s][f[i][j][k]]) ok = 0;
                }
            }
            if(ok) ans[i][0] = a, ans[i][1] = b, ans[i][2] = c;
        }
    }
    for(int i = 0; i < 16; ++i) {
        printf("id: %d\n", i);
        for(int j = 0; j < 3; ++j) {
            int x = ans[i][j];
            if(j==0) printf("A:\n");
            else if(j==1) printf("B:\n");
            else printf("C\n");
            for(int k = 0; k <= 1; ++k) {
                for(int l = 0; l <= 1; ++l) {
                    printf("%d ", mt[x][k][l]);
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("\n");
    }
    for(int i = 0; i < 16; ++i) {
        //printf("{%d, %d, %d},\n", ans[i][0], ans[i][1], ans[i][2]);
    }
    //printf("%d %d\n%d %d\n", mt[61][0][0], mt[61][0][1], mt[61][1][0], mt[61][1][1]);
}

/*
{0, 0, 61},
{1, 1, 77},
{1, 3, 77},
{1, 0, 77},
{3, 1, 77},
{0, 1, 77},
{2, 2, 78},
{3, 3, 79},
{3, 3, 77},
{2, 2, 74},
{0, 1, 79},
{3, 1, 79},
{1, 0, 79},
{1, 3, 79},
{1, 1, 79},
{0, 0, 23},
*/
#include<iostream>
#include <cstdio>
using namespace std;

const int N = 2050;
bool P[N][N];

void getSG(int n, int m)
{
    bool hasP = false;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            bool hasP = false;
            if(i > 1 && P[i - 1][j]) hasP = true;
            if(j > 1 && P[i][j - 1]) hasP = true;
            if(i > 1 && j > 1 && P[i - 1][j - 1]) hasP = true;
            P[i][j] = !hasP;
        }
    }
}
int main()
{
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF && n && m) {
        getSG(2, 2);
        /*for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                printf("%d ", P[i][j]);
            }
            printf("\n");
        }*/
        if(P[n % 2][m % 2]) {
            printf("What a pity!\n");
        } else {
            printf("Wonderful!\n");
        }
    }
}
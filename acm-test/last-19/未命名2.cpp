#include<iostream>
#include<cstdio>
using namespace std;

int c[1005][1105], a[1005], b[1005];
int main() {
    int n;
    cin >> n;
    int ii, jj;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            scanf("%d", &c[i][j]);
            if(c[i][j] == -1) {
                ii = i; 
                jj = j;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        if(i != ii) {
            b[0] = 0;
            for(int j = 1; j < n; ++j) {
                b[j] = b[j-1] + c[i][j] - c[i][j-1];
            }
            break;
        }
    }
    for(int j = 0; j < n; ++j) {
        if(j != jj) {
            a[0] = c[0][j] - b[j];
            for(int i = 1; i < n; ++i) {
                a[i] = a[i-1] + c[i][j] - c[i-1][j];
            }
            break;
        }
    }
    int ans = a[ii] + b[jj];
    printf("%d\n", ans);

}

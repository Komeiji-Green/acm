#include<bits/stdc++.h>
using namespace std;

int G[50][50];
int bit[50];
int main() {
    int L, R; cin >> L >> R;
    int M = R - L, n = 32;
    if(M == 0) {
        G[1][n] = L;
    } else {
        for(int i = 1; i < 23; ++i) {
            for(int j = i + 1; j < 23; ++j) {
                if(i == 1) G[i][j] = 1;
                else G[i][j] = (1<<(i-2));
            }
        }
        for(int i = 0; i < 21; ++i) {
            if((1<<i)&M) {
                int base=M&(~((1<<(i+1))-1));
                G[i+2][n]=base+L;
            }
        }
        G[1][n]=L;
    }

    int m = 0;
    cout << "YES" << endl;
    for(int i = 1; i <= n; ++i) for(int j = i + 1; j <= n; ++j) if(G[i][j]) ++m;
    cout << n << " " <<  m << endl;
    for(int i = 1; i <= n; ++i) for(int j = i + 1; j <= n; ++j) {
        if(G[i][j]) printf("%d %d %d\n", i, j, G[i][j]);
    }
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 505;

int G[N][N], w[N], l[N];

int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) G[i][j] = -2;
        for(int i = 1; i <= n; ++i) w[i] = l[i] = 0;
        if(n % 2 == 0) {
            for(int i = 1; i <= n; i += 2) {
                G[i][i+1]=G[i+1][i]=0;
            }
        }
        int m = (n-1) / 2;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(j == i) continue;
                if(G[i][j] != -2) continue;
                if(w[i] < m && l[j] < m) {
                    G[i][j] = 1, G[j][i] = -1;
                    w[i]++; l[j]++;
                } else if(l[i] < m && w[j] < m) {
                    G[i][j] = -1, G[j][i] = 1;
                    l[i]++; w[j]++;
                }
            }
        }
        bool f = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = i + 1; j <= n; ++j) {
                printf("%d ", G[i][j]);
                //if(G[i][j] == -2) f = 1;
            }
        }
        printf("\n");
        //if(f) printf("!!!!\n");
    }
}
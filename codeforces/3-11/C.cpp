#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 505;
char s[N][N]; int pos[N];

void chk(int &x, int y) {
    if(x < y) x = y;
}
int main() {
    int T, n, m;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; ++i) {
            scanf("%s", s[i] + 1);
        }
        for(int i = 0; i < n; ++i) pos[i] = 0;
        for(int i = 0; i < n; ++i) {
            if(i % 3 == 0) {
                for(int j = 1; j <= m; ++j) s[i][j] = 'X';
            } else {
                for(int j = 1; j <= m; ++j) {
                    if(s[i][j] == 'X') {
                        chk(pos[i-i%3], j);
                        if((i-i%3)+3>=n) {
                            for(int r = i-i%3; r <= i; ++r) s[r][j] = 'X';
                        }
                    }
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            if(i % 3 == 0) {
                int j = pos[i];
                if(j == 0) ++j;
                s[i+1][j] = 'X'; s[i+2][j] = 'X';
            }
        }
        for(int i = 0; i < n; ++i) printf("%s\n", s[i] + 1);
    }
}
#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
typedef long long ll;
const int N = 1005;
ll G[N][N], d[N][N], p[N][N];
void floyd() {
    rep(i, 1, n) rep(j, 1, n) {
        d[i][j] = G[i][j];
        p[i][j] = -1;
    }
    rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) {
        if(d[i][k] + d[k][j] < d[i][j]) {
            d[i][j] = d[i][k] + d[k][j];
            p[i][j] = p[i][k];
        }
    }
}
int main() {

}
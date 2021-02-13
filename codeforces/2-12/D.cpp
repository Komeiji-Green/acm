#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 505;
int a[maxn][maxn];

int f(int x) {
    return x * x * x * x;
}
int main() {
    int T, n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) {
        if((i+j)%2) {
            a[i][j] = 720720;
        } else {
            a[i][j] = 720720-f(a[i][j]);
        }
    }
    for(int i= 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

//720720
//
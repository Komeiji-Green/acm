#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2020;
int xx[N], yy[N], len[N];
int main() {
    int n;
    cin >> n;
    int x, y, s; // 2*x - y = k;
    for(int i = 1; i <= n; ++i) {
        len[i] = (n - i) / 2 + 1;
        xx[i] = 0, yy[i] = n - i;
    }
    for(int i = 1; i <= n; ++i) {
        int j = (i % 3); if(j == 0) j = 3;
        for(; j <= i; j += 3) {
            x = xx[j]; y = yy[j];
            for(int k = 1; k <= len[j]; ++k) {
                printf("%d %d %d\n", x, y, j);
                x -= 1; y -= 2;
            }
            xx[j] += 2; yy[j] -= 1;
        }
    }
}
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n = 17, m = n * (n - 1) / 2;
    printf("%d %d\n", n, m);
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) printf("%d %d\n", i, j);
    }
}
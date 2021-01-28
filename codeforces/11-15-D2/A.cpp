#include<bits/stdc++.h>
using namespace std;
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n); 
        printf("%d\n", n);
        for(int i = 1; i <= n; ++i) printf("%d ", i);
        printf("\n");
    }
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    int T;
    cin >> T;
    while(T--) {
        int x, y;
        scanf("%d %d", &x, &y);
        if(x < y) swap(x, y);
        if(x == y) printf("%d\n", x + y);
        else printf("%d\n", 2*x-1);
    }
}
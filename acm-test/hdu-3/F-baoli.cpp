#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int a[20], w[20];
int chk(int x, int d) {
    int len = 0;
    while(x) a[len++] = x % 10, x /= 10;
    for(int i = 0; i < 10; ++i) w[i] = 0;
    for(int i = 0; i < len; ++i) w[a[i]]++;
    for(int i = 0; i < 10; ++i) {
        if(i != d && w[i] >= w[d]) return 0;
    }
    return 1;
}
int gao(int x, int d) {
    int res = 0;
    for(int i = 1; i <= x; ++i) {
        if(chk(i, d)) res++;
    }
    return res;
}
int main() {
    int T;
    cin >> T;
    int l, r, d;
    while(T--) {
        scanf("%d %d %d", &l, &r, &d);
        printf("%d\n", gao(r, d) - gao(l-1, d));
    }
}
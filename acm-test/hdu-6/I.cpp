#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 23333;
char s[maxn];

int main() {
    int T, n;
    ll b, x;
    cin >> T;
    while(T--) {
        scanf("%lld %lld", &b, &x);
        if((b-1) % x == 0) {
            printf("T\n");
        } else {
            printf("F\n");
        }
    }
}
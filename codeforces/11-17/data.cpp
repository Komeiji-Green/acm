#include<bits/stdc++.h>
#include<ctime>
using namespace std;
typedef long long ll;
ll a[2005];
const ll mm = 100000;
bool cmp(ll a, ll b) {
    return a > b;
}
int main() {
    srand(time(NULL));
    int n = rand() % 2000 + 1, q = rand() % 2000 + 1;
    printf("%d %d\n", n, q);
    for(int i = 1; i <= n; ++i) a[i] = rand() % mm + 1;
    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; ++i) printf("%lld ", a[i]);
    printf("\n");
    for(int i = 1; i <= q; ++i) {
        int op = rand() % 2 + 1; int x; ll y;
        if(op == 1) {
            x = rand() % n + 1;
            y = rand() % mm + 1;
            printf("%d %d %lld\n", op, x, y);
        } else {
            x = rand() % n + 1;
            y = rand() % mm + 1;
            printf("%d %d %lld\n", op, x, y);
        }
    }
}

/*
9 11
93 91 64 58 46 39 36 18 13 
1 4 57
1 4 28
2 6 34
1 8 71
2 5 8
1 6 74
2 1 48
2 6 30
1 6 50
2 1 54
1 1 73
*/
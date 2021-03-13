#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 500007;
int a[N];
int main() {
    srand(time(NULL));
    int n = 50, q = 50;
    printf("%d %d\n", n, q);
    for(int i = 1; i <= n; ++i) a[i] = rand() % 100;
    for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
    printf("\n");

    int op, l, r, x;
    while(q--) {
        op = rand() % 2 + 1;
        l = rand() % n + 1; r = rand() % n + 1;
        if(l > r) swap(l, r);
        if(op == 1) {
            x = rand() % 100;
            printf("%d %d %d %d\n", op, l, r, x);
        } else {
            printf("%d %d %d\n", op, l, r);
        }
    }
}
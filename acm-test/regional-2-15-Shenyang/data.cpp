#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    srand(time(NULL));
    int T = 5;
    cout << T << endl;
    while(T--) {
        int n = 100000, m = 100000;
        printf("%d %d\n", n, m);
        for(int i = 1; i <= n; ++i) {
            int x = rand() % 1005, y = rand() % 1005;
            int c = rand() % n + 1;
            printf("%d %d %d\n", x, y, c);
        }
        for(int i = 1; i <= m; ++i) {
            int op;
            if(i % 2 == 1) {
                op = 3;
                int l = rand() % n + 1, r = rand() % n + 1;
                if(l > r) swap(l, r);
                printf("%d %d %d\n", op, l, r);
            } else {
                op = rand() % 2 + 1;
                if(op == 1) {
                    int k = rand() % n + 1;
                    int x = rand() % 1005, y = rand() % 1005;
                    printf("%d %d %d %d\n", op, k, x, y);
                } else {
                    int k = rand() % n + 1, c = rand() % n + 1;
                    printf("%d %d %d\n", op, k, c);
                }
            }
        }
    }
}
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

int rand(int _m) {
    return rand() % _m + 1;
}
int main() {
    srand(time(NULL));
    int szn = 10, szm = 10;
    

    int n = rand(100000), m = rand(100000);
    printf("%d %d\n", n, m);
    for(int i = 1; i <= m; ++i) {
        int op = rand(5), k = rand(i) - 1, a = rand(n), b;
        printf("%d %d %d ", op, k, a);
        if(op == 1 || op == 3 || op == 4) {
            b = rand(n);
            printf("%d ", b);
        }
        printf("\n");
    }
}
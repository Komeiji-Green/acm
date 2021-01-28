#include<cstdlib>
#include<cstdio>
#include<ctime>

int rand(int _m) {
    return rand() % _m + 1;
}
int main() {
    srand(time(NULL));
    int n = rand(6) + 2;
    printf("%d\n", n);
    for(int i = 0; i < n; ++i) {
        printf("%d ", rand(80));
    }
    printf("\n");
}
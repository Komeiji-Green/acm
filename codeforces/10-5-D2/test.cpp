#include<stdio.h>

int cnt = 0;
int main() {
    char c;
    while((c = getchar()) != '\n') {
        ++cnt;
    }
    printf("%d\n", cnt);
}
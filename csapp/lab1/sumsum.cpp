#include<stdio.h>

int sum(int a[], unsigned len) {
    int i, sum = 0;
    for(i = 0; i <= len - 1; i++) {
        sum += a[i];
    }
    return sum;
}

int a[10001];

int main() {
    sum(a, 0);
}

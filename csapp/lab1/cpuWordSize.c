#include<stdio.h>

int cpuWordSize() {
    return sizeof(int*)*8;
}

int main() {
    printf("ur WordSize is : %d", cpuWordSize());
}
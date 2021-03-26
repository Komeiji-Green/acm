#include<iostream>
using namespace std;

void printhex(unsigned char* p, int len) {
    for(int i = 0; i < len; ++i) printf(" %.2x", p[i]);
    printf("\n");
}
void printfloat(float f) {
    unsigned int x;
    unsigned int S, E, frac;
    memcpy(&x, &f, sizeof(f));
    E = (x>>23)&((1<<8)-1);
    S = (x>>31)&1;
    frac = x&((1<<23)-1);
    printf("%d %d %d\n", S?-1:1, E - 127, frac);
    
}
int main() {
    float f;
    for(;;) {
        scanf("%f", &f);
        //printf("%f\n", f);
        //printhex((unsigned char*)(&f), sizeof(f));
        printfloat(f);
        printf("output: %f\n\n", f);
        if(f == 0.0) break;
    }
}

// 1 10000001 010000...
// -1 2 1.01
/*
0 01111110 01101100011001100110011
*/
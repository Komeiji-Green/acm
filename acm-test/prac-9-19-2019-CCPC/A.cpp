#include<iostream>
#include<cstdio>
using namespace std;
typedef unsigned int uint;
int main() {
    int T;
    cin >> T;
    while(T--) {
        uint a, b, c;
        c = 0;
        scanf("%u %u", &a, &b);
        for(int i = 0; i < 32; i++) {
            int d1 = ((a >> i) & 1);
            int d2 = ((b >> i) & 1);
            if(d1 == 1 && d2 == 1) {
                c |= (1 << i);
            }
        }
        if(c == 0) c = 1;
        printf("%u\n", c);
    }
}
#include<bits/stdc++.h>
using namespace std;

int main() {
    unsigned int i = 3;
    printf("%u\n", i*-1);
    cout << (i*-1) << endl; // 2^32 - 3
    cout << (int)(i*-1) << endl; // -3
    // 说明：无符号和有符号的二进制表示一样，乘法运算规则相同，于是强转回来还是-3
}

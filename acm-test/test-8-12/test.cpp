#include<cstring>
#include <iostream>
#include<ctime>
int v[500000];
using namespace std;
int main()
{
    clock_t st, ed;
    st = clock();
    for(int i = 0; i < 500000; i++) {
        memset(v, 0, sizeof(v));
    }
    ed = clock();
    cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
}
#include<iostream>
#include <ctime>
using namespace std;
int main()
{
    clock_t st, ed;
    st = clock();
    for(int i = 0; i < 1000000000; i++);
    ed = clock();
    cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
}
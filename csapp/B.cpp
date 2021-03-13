#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int A[2048][2048], B[2048][2048];

void cpy(int a[2048][2048], int b[2048][2048]) {
    int n = 2048;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j )
            b[i][j] = a[i][j];
}

void cpy2(int a[2048][2048], int b[2048][2048]) {
    int n = 2048;
    for(int j = 0; j < n; ++j)
        for(int i = 0; i < n; ++i )
            b[i][j] = a[i][j];
}

int main() {
    srand(time(NULL));
    int n = 2048;
    for(int i = 0 ; i< n; ++i) for(int j = 0; j < n ;++j) A[i][j] = rand() % 100 + 1;
    clock_t st = clock(), ed;
    cpy(A, B);
    ed = clock();
    cout << (double)(ed-st)/1000 << endl;
    st = clock();
    cpy2(A, B);
    ed = clock();
    cout << (double)(ed-st)/1000 << endl;
}
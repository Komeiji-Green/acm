#include<iostream>
#include<cstdio>
using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        if(n % m == 0) printf("0\n");
        else printf("1\n");
    }
}
#include<bits/stdc++.h>
using namespace std;
int main() {
    srand(time(NULL));
    int n = rand() % 11 + 6;
    printf("%d\n", n);
    for(int i = 1; i <= n; ++i) {
        printf("%d ", rand() % n + 1);
    }
    cout << endl;
}
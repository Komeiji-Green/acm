#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    srand(time(NULL));
    int n = 10;
    cout << n << endl;
    for(int i = 1; i <= n; ++i) {
        printf("%d %d\n", rand() % 20, rand() % 20);
    }
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    srand(time(NULL));
    int T = 1;
    cout << 1 << endl;
    cout << 5 << endl;
    int n = 5;
    for(int i = 1; i <= n; ++i) printf("%d ", rand() % (2*n) + 1);
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int r[50];
int main() {
    srand(time(NULL));
    int T = 20;
    cout << T << endl;
    for(int i = 0; i <= 9; ++i) {
        r[i] = rand() % 500 + 1;
    }
    for(int i = 0; i <= 9; ++i) {
        printf("%d %d %d\n", 1, r[i], i);
    }
    for(int i = 0; i <= 9; ++i) {
        printf("%d %d %d\n", 1, r[i], i);
    }
}
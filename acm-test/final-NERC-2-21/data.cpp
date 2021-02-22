#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    srand(time(NULL));
    int q = 25;
    cout << q << endl;
    for(int i = 1; i <= 10; ++i) {
        printf("+ %d %d\n", i, rand() % 100 + 1);
    }
    /*for(int i = 1; i <= 10; ++i) {
        printf("? %d\n", i);
    }*/
    for(int i = 1; i <= 5; ++i) {
        printf("- %d\n", 2 * i);
    }
    for(int i = 1; i <= 10; ++i) {
        printf("? %d\n", i);
    }
    
}
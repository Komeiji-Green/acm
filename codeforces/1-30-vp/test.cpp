#include<bits/stdc++.h>
using namespace std;
int main() {
    int n = 6;
    int tot = 0;
    int p[20];
    for(int i = 1; i <= 6; ++i) p[i] = i;
    do {
        ++tot;
        for(int i = 1; i <= 3; ++i) printf("%d ", p[i]);
        printf("\n");
        sort(p + 4, p + n + 1, greater<int>());
    } while(next_permutation(p + 1, p + n + 1));
    printf("%d\n", tot);
}
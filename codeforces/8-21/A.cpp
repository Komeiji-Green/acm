#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n, k;
        scanf("%d %d", &n, &k);
        int ans = 0;
        if(n <= k) {
            ans = k - n;
        } else {
            if((n - k) % 2 == 0)
                ans = 0;
            else 
                ans = 1;
        }
        printf("%d\n", ans);
    }
}
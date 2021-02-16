#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

int a[N];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i= 1; i <=n ;++i) scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        int cnt = 0;
        for(int i = 1; i <= n; ++i) {
            ++cnt;
            if(i == n || a[i] != a[i + 1]) break;
        }
        printf("%d\n", n - cnt);
    }
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;

int a[N];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i<= n; ++i) scanf("%d", &a[i]);
        int maxv = 0, pre = 0, cur = 0, st = 0;
        while(1) {
            maxv = 0;
            for(int i = 1; i <= n; ++i) {
                if(i == pre) continue;
                if(a[i] > maxv) cur = i, maxv = a[i];
            }
            if(maxv == 0) break;
            st ^= 1; pre = cur; --a[pre];
        }
        if(st == 1) printf("T\n");
        else printf("HL\n");
    }
}
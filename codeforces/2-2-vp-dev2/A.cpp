#include<bits/stdc++.h>
using namespace std;

int a[233], cnt[233];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i =1 ; i<= n; ++i) cnt[i] =0;
        for(int i =1; i <= n; ++i) {
            scanf("%d", &a[i]); cnt[a[i]]++;
        }
        int maxv = 1;
        for(int i =1; i <= n; ++i) maxv = max(maxv, cnt[i]);
        printf("%d\n", maxv);
        
        
    }
}
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int a[100500];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        if(m & 1) {
            int hh = m / 2;
            for(int i = 1; i <= n; ++i) {
                int res = (a[i] <= hh);
                if(i == n) printf("%d\n", res);
                else printf("%d ", res);
            }
        } else {
            int hh = m / 2;
            int cnt = 0;
            for(int i = 1; i <= n; ++i) {
                if(a[i] == hh) cnt++;
            }
            cnt /= 2;
            for(int i = 1; i <= n; ++i ) {
                int res;
                if(a[i] < hh) res = 1;
                else if(a[i] > hh) res = 0;
                else {
                    if(cnt > 0) res = 1;
                    else res = 0;
                    --cnt;
                }
                if(i == n) printf("%d\n", res);
                else printf("%d ", res);
            }
        }
    }
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 333333;
const int inf = 0x3f3f3f3f;

int li[10];

// 0 1
// 3 2
int main() {
    int T, n, cnt[4], tmp[4];
    cin >> T;
    while(T--) {
        scanf("%d %d %d %d %d", &n, &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
        bool ok = 0;
        for(int i = 0; i < 16; ++i) {
            for(int j = 0; j < 4; ++j) {
                if((1<<j)&i) {
                    li[j] = 1;
                } else {
                    li[j] = 0;
                }
            }
            for(int j = 0; j < 4; ++j) {
                cnt[j] = tmp[j]-(li[j] + li[(j+1)%4]);
            }
            bool f = 1;
            for(int j = 0; j < 4; ++j) {
                if(cnt[j] < 0 || cnt[j] > (n-2)) f = 0;
            }
            if(f) ok = 1;
            
        }
        if(ok) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
    }
}
#include<bits/stdc++.h>
using namespace std;

int a[100];
int solve() {
    for(int i = 1; i <= 6; ++i) {
        for(int j = 1; j <= 6; ++j) {
            a[i*j]++;
        }
    }
    int res = 0;
    for(int i = 1; i <= 36; ++i) {
        res += a[i] * a[i];
    }
    cout << res << endl;
}

int bit[10], vis[10];
int cnt = 0;
int main() {
    for(int i = 1; i <= 6666; ++i) {
        for(int j = 1, x = i; j <= 4; ++j) {
            bit[j] = x % 10;
            x /= 10;
        }
        bool f = 1;
        for(int j = 0; j <= 9; ++j) vis[j] = 0;
        for(int j = 1; j <= 4; ++j) {
            if(bit[j] < 1 || bit[j] > 6) f = 0;
            if(vis[bit[j]]) f = 0;
            vis[bit[j]]=1;
        }
        if(f&&bit[1]*bit[4]==bit[2]*bit[3]) {
            cnt++;
        }
    }
    cout << cnt << endl;
}
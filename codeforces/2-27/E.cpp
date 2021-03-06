#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 40;

ll bit[65];
ll a[N][N];
int xx[100], yy[100];
int main() {
    int n, q; cin >> n;
    for(int i = 0; i < 60; ++i) bit[i] = (1ll<<i);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            a[i][j] = bit[i+j];
            if(i%2) a[i][j]*=2ll;
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl; cout.flush();
    }
    cin >> q;
    ll sum;
    while(q--) {
        cin >> sum;
        int m = 2 * n - 1;
        xx[0] = 1, yy[0] = 1;
        sum -= 1;
        int x = 0, y = 0;
        for(int i = 1; i < m; ++i) {
            if(sum & (bit[i])) { // 偶数
                if(x % 2 == 0) y++;
                else x++;
                xx[i] = x + 1, yy[i] = y + 1;
                sum -= bit[i];
            } else { // 奇数
                if(x % 2 == 0) x++;
                else y++;
                xx[i] = x + 1, yy[i] = y + 1;
                sum -= (bit[i]<<1);
            }
        }
        for(int i = 0; i < m; ++i) {
            cout << xx[i] << " " << yy[i] << endl; cout.flush();
        }
    }
}
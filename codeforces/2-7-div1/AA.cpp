#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn];

int main() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << "! 1" << endl;
        cout.flush();
    } else {
        a[0] = a[n + 1] = 0x3f3f3f3f;
        int le = 1, ri = n, k1, k2;
        //cout << "? " << le << endl; cin >> a[le];
        //cout << "? " << le + 1 << endl; cin >> a[le + 1];
        //if(a[1] < a[0])
        int mid = ((le + ri) >> 1);
        while(le < ri) {
            cout << "? " << mid << endl; cout.flush(); cin >> k1;
            cout << "? " << mid + 1 << endl; cout.flush(); cin >> k2;
            if(k1 < k2) {
                ri = mid;
            } else {
                le = mid + 1;
            }
            mid = ((le + ri) >> 1);
        }
        cout << "! " << mid << endl; cout.flush();
    }
    return 0;
}
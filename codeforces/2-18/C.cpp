#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

int main() {
    int n, p, q;
    cin >> n;
    cout << "? " << 1 << " " << n << endl; cout.flush();
    cin >> p;

    bool f = 0;
    if(p < n) {
        cout << "? " << p << " " << n << endl; cout.flush();
        cin >> q;
        if(q == p) f = 1;
    }
    if(f) { // ans in you
        int le = p + 1, ri = n;
        int mid = ((le + ri) >> 1);
        while(le < ri) {
            cout << "? " << p << " " << mid << endl; cout.flush(); cin >> q;
            if(q == p) {
                ri = mid;
            } else {
                le = mid + 1;
            }
            mid = ((le + ri) >> 1);
        }
        cout << "! " << mid << endl; cout.flush();
    } else {
        int le = 1, ri = p - 1;
        int mid = ((le + ri + 1) >> 1);
        while(le < ri) {
            cout << "? " << mid << " " << p << endl; cout.flush(); cin >> q;
            if(q == p) {
                le = mid;
            } else {
                ri = mid - 1;
            }
            mid = ((le + ri + 1) >> 1);
        }
        cout << "! " << mid << endl; cout.flush();
    }
}
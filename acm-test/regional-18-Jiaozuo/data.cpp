#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int T = 22;
    cout << T << endl;
    while(T--) {
        int n = 3, m = 1500;
        cout << n << " " << m << endl;
        int x = 1;
        for(int i = 1; i <= n; ++i, ++x) {
            cout << x << " ";
            cout << x << " ";
            cout << x << " ";
            cout << x << " ";
            cout << endl;
        }
    }

}
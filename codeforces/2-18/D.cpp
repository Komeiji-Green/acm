#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
const int inf = 0x3f3f3f3f;

int a[N], val[N], pre1[N], pre2[N], n, k;

int chk(int m) {
    val[0] = 0;
    for(int i = 1; i <= n; ++i) {
        if(a[i] >= m) val[i] = val[i-1] + 1;
        else val[i] = val[i-1] - 1;  
    }
    pre1[0] = inf;
    for(int i = 1; i <= n; ++i) {
        if(i % 2) {
            pre1[i] = min(val[i], pre1[i-1]);
        } else {
            pre1[i] = pre1[i-1];
        }
    }
    pre2[0] = 0;
    for(int i = 1; i <= n; ++i) {
        if(i % 2 == 0) {
            pre2[i] = min(val[i], pre2[i-1]);
        } else {
            pre2[i] = pre2[i-1];
        }
    }
    bool f = 0;
    for(int i = k; i <= n; ++i) {
        int cur = val[i];
        int j = i - k;
        if(i % 2) {
            if(cur - pre1[j] >= 2 || cur - pre2[j] >= 1) f = 1;
        } else {
            if(cur - pre1[j] >= 1 || cur - pre2[j] >= 2) f = 1;
        }
        if(f) return 1;
    }
    return 0;
}
int main() {
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int le = 1, ri = n;
    int mid = ((le + ri + 1) >> 1);
    while(le < ri) {
        if(chk(mid)) {
            le = mid;
        } else {
            ri = mid - 1;
        }
        mid = ((le + ri + 1) >> 1);
    }
    printf("%d\n", mid);
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
int tag[N], p[N], le[N], ri[N];
int n;
bool in(int x) {
    return x-1 >= 1 && x+1 <= n;
}
int sgn(int x) {
    if(x == 0) return 0;
    else return x < 0 ? -1 : 1;
}
int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%d", &p[i]);
    for(int i = 2, j = 1; i <= n; ++i) {
        if(i == n || sgn(p[i]-p[i-1]) == sgn(p[i]-p[i+1])) {
            le[i] = i - j;
            j = i;
        }
    }
    for(int i = n - 1, j = n; i >= 1; --i) {
        if(i == 1 || sgn(p[i]-p[i-1]) == sgn(p[i]-p[i+1])) {
            ri[i] = j - i;
            j = i;
        }
    }
    int cnt = 0, maxv = 0, x = 0;
    for(int i = 1; i <= n; ++i) {
        if(i == 1 && p[i+1] < p[i] || i == n && p[i-1] < p[i] || in(i) && p[i+1] < p[i] && p[i-1] < p[i]) {
            if(le[i] > maxv) {
                cnt = 1; maxv = le[i]; x = i;
            } else if(le[i] == maxv) {
                ++cnt; x = i;
            }
            if(ri[i] > maxv) {
                cnt = 1; maxv = ri[i]; x = i;
            } else if(ri[i] == maxv) {
                if(ri[i] != le[i]) {
                    ++cnt; x = i;
                } 
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        //printf("L: %d, R: %d\n", le[i], ri[i]);
    }
    //printf("%d %d %d\n", cnt, maxv, x);
    int ans = 0;
    if(cnt > 1) ans = 0;
    else {
        if(le[x] != ri[x]) ans = 0;
        else {
            if(le[x] % 2 == 0) ans = 1;
            else ans = 0;
        }
    }
    printf("%d\n", ans);
}
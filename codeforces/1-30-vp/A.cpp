#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int bit[31];
const int maxn = 233333 * 10;
int t[maxn], rev[maxn], id[maxn], v[maxn];
int hbit(int x) {
    int hb = -1;
    for(int i = 0; i < 25; ++i) {
        if((1<<i)&x) hb = i;
    }
    return hb;
}
int main() {
    int n, m;
    cin >> n >> m;
    int cnt = n + m;
    int hb = -1;
    for(int i = 0; i < 25; ++i) {
        if((1<<i)&m) bit[i] = 1, hb = i;
    }
    int r = 0;
    for(int i = 0; i < hb; ++i) {
        if(!bit[i]) r += (1<<i);
    }
    if(n < r) {
        printf("-1\n");
    } else {
        int h = hb + 1;
        int mm = (1<<h);
        for(int i = 1; i < mm; ++i) {
            int j = hbit(i);
            if(bit[j]) t[i] = 2;
            else {
                t[i] = 1; --n;
            }
        }
        while(n) {
            int len = (1<<h); rev[0] = 0;
            for(int i = 1; i < len; ++i) 
                rev[i] = (rev[i>>1]>>1)|((i&1)<<(h-1));
            for(int i = 0; i < len && n; ++i) {
                t[rev[i]|len] = 1; --n;
            }
            ++h;
        }
        int j = 0;
        for(int i = 1; j < cnt; ++i) {
            if(t[i]) {
                id[i] = ++j;
                //printf("%d %d %d\n", j, i, t[i]);
                v[j] = i;
            }
        }
        for(int i = 1; i <= cnt; ++i) {
            int x = v[i];
            int lch = (t[x<<1]) ? id[x<<1] : 0;
            int rch = (t[x<<1|1]) ? id[x<<1|1] : 0;
            printf("%d %d %d\n", t[x], lch, rch);
        }
    }
}
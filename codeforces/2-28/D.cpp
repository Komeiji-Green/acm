#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10005;
const int inf = 0x3f3f3f3f;
int bitu[60], bitv[60];
ll bit[60];

void print(ll x) {
    for(int i = 20; i >= 0; --i) {
        if((x>>i)&1ll) printf("1");
        else printf("0");
    }
    printf("\n");
}
int main() {
    int q;
    cin >> q;
    ll u, v;
    while(q--) {
        scanf("%lld %lld", &u, &v);
        bool f = 1;
        ll x;
        if(u > v) f = 0;
        else if(u == v) f = 1;
        else {
            for(int i = 0; i < 50; ++i) bit[i] = (1ll<<i);
            int p = 0;
            ll uu, vv;
            for(; p < 45; ++p) {
                //printf("u: "); print(u); 
                //printf("v: "); print(v);
                if(u == v) {
                    f = 1; break;
                }
                if(u > v) {
                    f = 0; break;
                }
                uu = ((u>>p) & 1ll);
                vv = ((v>>p) & 1ll);
                if(uu == vv) continue;
                if(uu == 0 && vv == 1) {
                    f = 0; break;
                } else {
                    x = bit[p];
                    while((u>>(p+1)) & 1ll) {
                        ++p;
                        if((v>>p) & 1ll) {
                            x |= bit[p];
                        }
                    }
                    //printf("x: "); print(x);
                    u += x;
                }
                //printf("\n");
            }
            if(u < v) f = 0;
        }
        if(f) printf("YES\n");
        else printf("NO\n");
    }

}

/*
*/
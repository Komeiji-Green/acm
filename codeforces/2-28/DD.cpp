#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10005;
const int inf = 0x3f3f3f3f;
int bitu[60], bitv[60];
ll bit[60];
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
            int p = 0;
            while(p < 40 && ((u>>p)&1ll) != ((v>>p)&1ll)) ++p;
            if(!((u>>p)&1ll) && ((v>>p)&1ll)) f = 0;
        }
        if(f) printf("YES\n");
        else printf("NO\n");
    }

}
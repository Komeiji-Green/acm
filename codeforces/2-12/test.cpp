#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2020;
// 素因数分解 
int p[maxn], l[maxn], cnt2 = 0;
void Fact(ll x) {
    cnt2 = 0;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            p[++cnt2] = i; l[cnt2] = 0;
            while(x % i == 0) {
                x /= i; ++l[cnt2];
            }
        }
    }
    if(x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[++cnt2] = x; l[cnt2] = 1;
    }
}
ll f(ll x) {
    return x*x*x*x;
}
int li[105];
bool vis[10];
int o[10] = {0, 16, 9, 5, 7, 11, 13};
ll p[20] = {0, 1, 16, 81, 16, 625, 1296, 2401, 16, 81, 10000, 14641, 1296, 28561, 38416, 50625, 16};

vector<ll> vec[10];
set<ll> mp;
int main() {
    int tot = 0;
    ll x;
    const ll M = 1e6;
    for(ll i = 1; (x=f(i)) <= M; ++i) {
        li[++tot] = x;
        if(x == 707281) printf("%lld\n", i);
        if(x == 50625) printf("%lld\n", i);
        mp.insert(x);
    }
    for(int i= 1; i <= tot; ++i) {
        printf("%lld: ", li[i]);
        Fact(li[i]);
        for(int k=1; k <= cnt2; ++k) {
                printf("(%d: %d) ", p[k], l[k]);
            } printf("\n");
    }
    for(int i = 1; i <= tot; ++i) {
        for(int j = i + 1; j <= tot; ++j) {
            for(int w = j + 1; w <= tot; ++w) {
                bool f = 1;
                for(int k = 1; k <= 6; ++k) {
                    if((li[i] % o[k]) && (li[j] % o[k]) && (li[w] % o[k])) f = 0;
                }
                if(!f) continue;
                printf("%lld %lld %lld\n", li[i], li[j], li[w]);
            }
        }
    }

    for(int k = 1; k <= 6; ++k) {
        for(int i = 1; i <= tot; ++i) {
            if(li[i] % o[k] == 0) vec[k].push_back(li[i]);
        }
    }
    
    const ll D = 194480;
    x = 63;
    
}

const ll tt = 16 * 7 * 11 * 13 * 41;

/*
707281 - 50625: (2: 4) (7: 1) (11: 1) (13: 1) (41: 1)
*/

/*
194480: (2: 4) (5: 1) (11: 1) (13: 1) (17: 1) 
331760: (2: 4) (5: 1) (11: 1) (13: 1) (29: 1) 
530816: (2: 7) (11: 1) (13: 1) (29: 1)        
34320: (2: 4) (3: 1) (5: 1) (11: 1) (13: 1)   
656656: (2: 4) (7: 1) (11: 1) (13: 1) (41: 1) 
549120: (2: 8) (3: 1) (5: 1) (11: 1) (13: 1) 
*/
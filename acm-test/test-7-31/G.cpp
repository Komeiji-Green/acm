#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1e7 + 5;
ll prime[maxn];
bool isnt[maxn];
int cnt = 0;

void Prime(int n)
{
    isnt[1] = 1; cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) prime[++cnt] = i;
        for(int j = 1; j <= cnt; j++) {
            if(i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}

bool isntPrime(ll n) {
    for(int i = 1; i <= cnt; i++) {
        if(n % prime[i] == 0) return true;
    }
    return false;
}


ll Mul(ll a, ll k, ll p) {
    ll ans = 0;
    while(k) {
        if(k & 1) ans = (ans + a) % p;
        k >>= 1; a = (a + a) % p;
    }
    return ans;
}

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = Mul(ans, a, p);
        k >>= 1; a = Mul(a, a, p);
    }
    return ans;
}


int main()
{
    Prime(10000000);
    int T;
    cin >> T;
    while(T--) {
        ll P;
        cin >> P;
        ll ans = 1;
        for(ll q = P - 2; isntPrime(q); q--) {
            ans = Mul(ans, q, P);
        }
        ans = Pow(ans, P - 2, P);
        cout << ans << endl;
        
    }
}
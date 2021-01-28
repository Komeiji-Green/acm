#include<bits/stdc++.h>
//#pragma comment(linker, "/STACK:102400000,102400000")
using namespace std;
typedef long long ll;

const int maxn = 10000000 + 5;
bool isnt[maxn];
ll prime[maxn];
int dis[maxn];
ll cnt = 0;

ll phi[maxn];
void Sieve(int n) {
    isnt[1] = true;
    phi[1] = 1;
    //mu[1] = 1;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1; //mu[i] = -1;
            //dis[i] = dis[phi[i]] + 1;
            // d[i] = 2; q[i] = 1;
            // D[i] = i + 1; q[i] = 1;
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                phi[x] = phi[i] * prime[j]; // mu[x] = 0;
                // d[x] = d[i] / (q[i] + 1) * (q[i] + 2), q[x] = q[i] + 1;
                // D[x] = D[i] / (prime[j] ^ (q[i] + 1) - 1) * (prime[j] ^ (q[i] + 2) - 1), q[x] = q[i] + 1;
                break;
            } else {
                phi[x] = phi[i] * (prime[j] - 1); // mu[x] = -mu[i]
                // d[x] = 2 * d[i], q[x] = 1;
                // D[x] = (prime[j] + 1) * D[i], q[x] = 1;
            }
        }
        dis[i] = dis[phi[i]] + 1;
    }
}


int main() {
    Sieve(10000000);
    int ans = 0;
    int cnt = 0;
    for(int i = 1; i <= 10000000; ++i) {
        if(5 * phi[i] < 4 * i) ++cnt;
        if(dis[i] > ans) ans = dis[i];
    }
    cout << ans << endl;
    cout << cnt << endl;
}

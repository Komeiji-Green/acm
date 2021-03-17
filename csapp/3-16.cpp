#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10000000 + 5;
bool isnt[maxn];
int prime[maxn];
int minv[maxn];
int cnt = 0;
void Prime(int n) {
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++) {
            if (1ll * i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    int n = 1000000;
    Prime(n);
    ll sum = 0;
    for(int x = 1; x <= n; ++x) {
        //if(!isnt[x]) ++sum;
        for(int i = 1; i <= cnt; ++i) {
            ++sum;
            if(x % prime[i] == 0) break;
        }
    }
    int p = prime[cnt];
    double ans = 0, cur = 1.0;
    for(int i = 1; i <= cnt && 1ll * prime[i] * prime[i] <= p; ++i) {
        ans += cur;
        cur *= (1.0 - 1 / prime[i]);
    }
    cout << ans << endl;
    cout << (double)sum / n << endl;
}
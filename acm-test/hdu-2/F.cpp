#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int maxn = 2000007;
const ll mod = 998244353;
ull f[maxn];

unordered_map<ull, int> mp;

int a[maxn], b[maxn], c[maxn];
int main() {
    int T;
    cin >> T;
    f[1] = 1; f[2] = 2;
    mp.reserve(1e7);
    mp[1] = 1; mp[2] = 2;
    for(int i = 3; i < maxn; ++i) {
        f[i] = (f[i-1] + f[i-2]);
        mp[f[i]] = i;
        //tmp[f[i]]++;
    }
    
    while(T--) {
        int n, m, p;
        scanf("%d", &n); for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        scanf("%d", &m); for(int i = 1; i <= m; ++i) scanf("%d", &b[i]);
        scanf("%d", &p); for(int i = 1; i <= p; ++i) scanf("%d", &c[i]);
        ull A = 0, B = 0, C = 0;
        for(int i = 1; i <= n; ++i) A += (ull)a[i]*f[i];
        for(int i = 1; i <= m; ++i) B += (ull)b[i]*f[i];
        for(int i = 1; i <= p; ++i) C += (ull)c[i]*f[i];
        ull del = A*B-C;
        //cout << del << endl;
        int idx = mp[del];
        printf("%d\n", idx);
    }
}
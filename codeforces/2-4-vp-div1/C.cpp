#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 233333;
char s[maxn];

ll cnt[30], val[26];
int main() {
    int n; ll m;
    cin >> n >> m;
    scanf("%s", s + 1);
    for(int i = 0; i < 26; ++i) val[i] = (1ll << i);
    m -= val[s[n]-'a'] - val[s[n-1]-'a'];
    for(int i = 1; i <= n - 2; ++i) {
        cnt[s[i]-'a']++;
    }
    for(int i = 0; i < 26; ++i) m += cnt[i] * val[i];
    for(int i = 0; i < 26; ++i) val[i] *= 2ll;
    if(m < 0 || m % 2) {
        printf("NO\n");
    } else {
        ll d;
        for(int i = 25; i >= 0; --i) {
            d = m / val[i];
            if(d <= cnt[i]) {
                m %= val[i];
            } else {
                m -= cnt[i] * val[i];
            }
        }
        if(m) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
}
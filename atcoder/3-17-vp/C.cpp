#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
const int mod = 10;
const int phi = 4;

int cnt[26];
char s[N];

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    ll ans = 0;
    for(int i = n; i >= 1; --i) {
        cnt[(s[i]-'a')]++;
        if(i < n && s[i] == s[i+1]) {
            int len = n - i + 1;
            ans += (len - cnt[s[i]-'a']);
            cnt[s[i]-'a'] = len;
            for(int j = 0; j < 26; ++j) {
                if(j == (s[i]-'a')) continue;
                else cnt[j] = 0;
            }
        }
    }
    printf("%lld\n", ans);
}
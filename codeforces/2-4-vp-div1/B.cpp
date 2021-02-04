#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
char s[maxn];
ll cnt[maxn], ans[maxn], cnt2[maxn];
int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    ll x, y;
    cin >> x >> y;
    if(x < y) {
        swap(x, y);
        for(int i = 1; i <= n; ++i) {
            if(s[i] == '1') s[i] = '0';
            else if(s[i] == '0') s[i] = '1';
        }
    }
    // 11110000
    ll sum = 0, cur, tot, res;
    cnt[0] = 0;
    for(int i = 1; i <= n; ++i) {
        cnt[i] = cnt[i-1];
        if(s[i] == '1') cnt[i]++;
    }
    cnt2[n+1] = 0;
    for(int i = n; i >= 1; --i) {
        cnt2[i] = cnt2[i+1];
        if(s[i] == '1') cnt2[i]++;
    }
    //printf("cnt\n");
    //for(int i = 1; i <= n; ++i) printf("%lld ", cnt2[i]);
    //cout << endl;
    for(int i = 1; i <= n; ++i) {
        cur = cnt[i-1]; res = cnt2[i+1];
        if(s[i] == '0' || s[i] == '?') {
            sum += y * cur + res * x;
        } else {
            sum += x * (i - 1 - cur) + y * (n - i - res);
        }
        //printf("sum: %lld\n", sum);
    }
    cnt[0] = 0;
    for(int i = 1; i <= n; ++i) {
        cnt[i] = cnt[i-1];
        if(s[i] == '1' || s[i] == '?') cnt[i]++;
    }
    int num = 0; 
    ans[0] = sum;
    for(int i = 1; i <= n; ++i) {
        if(s[i] == '?') {
            ++num;
            cur = cnt[i-1]; res = cnt2[i+1];
            ll c1 = y * cur + res * x;
            ll c2 = x * (i-1-cur) + y * (n-i-res);
            ll del = c2 - c1;
            ans[num] = ans[num-1] + 2 * del;
        }
    }
    ll minv = sum;
    for(int i = 1; i <= num; ++i) {
        minv = min(minv, ans[i]);
    }
    printf("%lld\n", minv / 2); 
}
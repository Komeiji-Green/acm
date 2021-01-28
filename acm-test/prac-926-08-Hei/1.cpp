#include<iostream>
#include<cstdio>
using namespace std;

typedef long long ll;

const int maxn = 233333;

char s[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%s", s);
        char c = s[0];
        ll cnt = 0, cur = 1;
        for(int i = 1; s[i]; ++i) {
            if(s[i] == c) {
                ++cur;
            } else {
                cnt += cur * (1 + cur) / 2;
                cur = 1;
                c = s[i];
            }
        }
        cnt += cur * (1 + cur) / 2;
        printf("%lld\n", cnt);
    }
}
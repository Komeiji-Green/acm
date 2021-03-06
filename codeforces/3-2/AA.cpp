#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 333333;
const int inf = 0x3f3f3f3f;

char s[maxn];
int mp[10];
int stk[maxn];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%s", s);
        n = strlen(s);
        bool f = 0;
        for(int i = 0; i < 8; ++i) {
            for(int j = 0; j <= 2; ++j) {
                if((1<<j)&i) {
                    mp[j] = 1;
                } else {
                    mp[j] = 0;
                }
            }
            int top = 0;
            bool ok = 1;
            for(int j = 0; j < n; ++j) {
                if(mp[s[j]-'A']) {
                    if(top > 0) --top;
                    else {
                        ok = 0; break;
                    }
                } else {
                    ++top;
                }
            }
            if(top) ok = 0;
            if(ok) f = 1;
        }
        if(f) printf("YES\n");
        else printf("NO\n");
    }
}
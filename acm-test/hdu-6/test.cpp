#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 23333;
char s[maxn];

int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%s", s);
        int n = strlen(s);
        int c1 = 0, c0 = 0;
        bool f = 1;
        for(int i = 1; i < n; ++i) {
            if(s[i] == '1' && s[i-1] == '1') c1++;
            if(s[i] == '0' && s[i-1] == '0') {
                if(c1 > 0) f = 0;
            }
        }
        if(f) printf("YES\n");
        else printf("NO\n");
    }
}
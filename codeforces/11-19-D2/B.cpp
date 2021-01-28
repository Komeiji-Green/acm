#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
char s[maxn];
int t1, t2;
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%s", s);
        t1 = t2 = 0;
        int ans = 0;
        for(int i = 0; s[i]; ++i) {
            if(s[i] == '(') ++t1;
            else if(s[i] == ')' && t1 > 0) {
                --t1;
                ++ans;
            } else if(s[i] == '[') ++t2;
            else if(s[i] == ']' && t2 > 0) {
                --t2;
                ++ans;
            }
        }
        printf("%d\n", ans);
    }
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
char s[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        queue<int> q;
        int le = 0, ri = 0;
        bool f = 1;
        for(int i = 1; i <= n; ++i) {
            if(s[i] == '*') {
                q.push(i);
            } else if(s[i] == '(') {
                ++le;
            } else if(s[i] == ')') {
                if(le > 0) {
                    --le;
                } else {
                    if(q.empty()) {
                        f = 0; break;
                    } else {
                        int x = q.front(); q.pop();
                        s[x] = '(';
                    }
                }
            }
        }
        while(!q.empty()) q.pop();
        for(int i = n; i >= 1 && f; --i) {
            if(s[i] == '*') q.push(i);
            else if(s[i] == ')') {
                ++ri;
            } else if(s[i] == '(') {
                if(ri > 0) --ri;
                else {
                    if(q.empty()) {
                        f = 0; break;
                    } else {
                        int x = q.front(); q.pop();
                        s[x] = ')';
                    }
                }
            }
        }
        if(!f) {
            printf("No solution!\n");
        } else {
            for(int i= 1; i <= n; ++i) {
                if(s[i] != '*') putchar(s[i]);
            }
            printf("\n");
        }
    }
}
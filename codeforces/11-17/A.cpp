#include<bits/stdc++.h>
using namespace std;

const int maxn = 1005;
char s[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, c0, c1, h;
        scanf("%d%d%d%d",&n,&c0,&c1,&h);
        scanf("%s", s);
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '0') sum += min(c0, c1 + h);
            else sum += min(c1, c0 + h);
        }
        printf("%d\n", sum);
    }
}
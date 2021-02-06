#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
const int maxn = 333333;
char s[maxn];
int vis[maxn];

int u, d, l, r;
int main() {
    int T;
    cin >> T;
    while(T--) {
        int x, y;
        scanf("%d %d", &x, &y);
        scanf("%s", s);
        u=d=l=r=0;
        for(int i = 0; s[i]; ++i) {
            if(s[i] == 'U') ++u;
            if(s[i] == 'D') --d;
            if(s[i] == 'L') --l;
            if(s[i] == 'R') ++r;
        }
        if(x >= l && x <= r && y >= d && y <= u) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}
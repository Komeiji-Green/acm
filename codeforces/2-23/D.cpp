#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
char x[N], y[N];
bool vis[N];
int main() {
    int a, b, k, n;
    cin >> a >> b >> k;
    n = a + b;
    x[n] = y[n] = '\0';
    if(b == 1 || a == 0) {
        if(k == 0) {
            printf("Yes\n");
            for(int i = 0; i < b; ++i) x[i] = '1';
            for(int i = 0; i < a; ++i) x[i + b] = '0';
            x[a + b] = '\0';
            printf("%s\n%s\n", x, x);
        } else {
            printf("No\n");
        }
    } else {
        --b;
        if(k < a + b) {
            printf("Yes\n");
            x[0] = y[0] = '1';
            int st = 1, ed = st + k;
            if(st != ed) {
                x[st] = '1'; y[st] = '0';
                x[ed] = '0'; y[ed] = '1';
                --a; --b;
                vis[st] = vis[ed] = 1;
            }
            for(int i = 1; i < n; ++i) {
                if(!vis[i]) {
                    if(a) {
                        x[i] = y[i] = '0'; --a;
                    } else {
                        x[i] = y[i] = '1';
                    }
                }
            }
            printf("%s\n%s\n", x, y);
        } else {
            printf("No\n");
        }
    }

}
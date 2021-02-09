#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
const int inf = 0x3f3f3f3f;
int a[maxn], dp[maxn][3], col[maxn][3];

int cnt[maxn], link[maxn], last[maxn];
int le, ri;
int main() {
    int n;
    cin >> n;
    for(int i = 1; i<= n; ++i) scanf("%d", &a[i]);
    int tot = 1; cnt[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(a[i] == a[tot]) cnt[tot]++;
        else {
            ++tot;
            a[tot] = a[i]; cnt[tot] = 1;
        }
    }
    for(int i = 1; i <= n; ++i) {
        link[i] = last[a[i]];
        last[a[i]] = i;
    }
    for(int i = 1; i <= n; ++i) {
        
    }
}
/*
11
1 1 1 2 3 2 2 2 1 1 1

8
*/

/*
13
1 1 1 2 2 3 4 2 2 2 1 1 1

10
*/
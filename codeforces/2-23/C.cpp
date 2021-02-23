#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
char s[N], t[N];
int le[N], ri[N];
int main() {
    int n, m;
    cin >> n >> m;
    scanf("%s %s", s + 1, t + 1);
    for(int i = 1, j = 1; i <= m; ++i, ++j) {
        while(j <= n && s[j] != t[i]) ++j;
        le[i] = j; //printf("%d: %d\n", i, j);
    }
    for(int i = m, j = n; i >= 1; --i, --j) {
        while(j >= 1 && s[j] != t[i]) --j;
        ri[i] = j;
    }
    int ans = 0;
    for(int i = 1; i < m; ++i) {
        int l = le[i], r = ri[i + 1];
        ans = max(ans, r - l);
    }
    printf("%d\n", ans);

}
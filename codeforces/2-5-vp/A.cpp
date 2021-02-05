#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
const int maxn = 333333;
char s[maxn];
int vis[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &k);
        scanf("%s", s);
        for(int i = 0; i < k; ++i) vis[i] = -1;
        bool f = 1;
        for(int i = 0; i < n; ++i) {
            if(s[i] != '?') {
                int c = s[i] - '0';
                int tag = vis[i % k];
                if(tag != -1 && tag != c) {
                    f = 0; break;
                }
                vis[i % k] = c;
            }
        }
        for(int i = 0; i < k; ++i) {
            if(vis[i]==-1) continue;
            for(int j = i; j < n; j += k) {
                s[j] = vis[i] + '0';
            }
        }
        int cnt0 = 0, cnt1 = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '1') ++cnt1;
            if(s[i] == '0') ++cnt0;
            if(i >= k - 1) {
                if(cnt1 > k / 2 || cnt0 > k / 2) {
                    f = 0; break;
                }
                if(s[i - k + 1] == '1') --cnt1;
                if(s[i-k+1] == '0') --cnt0;
            }
        }
        if(f) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}
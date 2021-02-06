#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn], b[maxn], c[maxn];
int vis[maxn], cnt[maxn], ans[maxn], last[maxn];
vector<int> li[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, m; scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) vis[i] = cnt[i] = 0;
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for(int i = 1; i <= n; ++i) scanf("%d", &b[i]);
        for(int i = 1; i <= m; ++i) scanf("%d", &c[i]);
        for(int i = 1; i <= n; ++i) vis[b[i]]++;
        //vector<int> vec; // 无关项
        //for(int i = 1; i <= m; ++i) if(!vis[c[i]]) vec.push_back(i);
        bool f = 1;
        if(!vis[c[m]]) f = 0;
        for(int i = 1; i <= n; ++i) li[i].clear();
        if(f) {
            for(int i = 1; i <= n; ++i) {
                if(a[i] != b[i]) {
                    li[b[i]].push_back(i);
                    cnt[b[i]]++;
                }
            }
            for(int i = 1; i <= n; ++i) {
                if(!li[b[i]].size()) {
                    li[b[i]].push_back(i);
                }
            }
            for(int i = 1; i <= m; ++i) {
                if(!vis[c[i]]) continue;
                cnt[c[i]]--;
            }
            for(int i = 1; i <= n; ++i) {
                if(cnt[i] > 0) f = 0;
            }
        }
        if(!f) {
            printf("NO\n");
        } else {
            printf("YES\n");
            for(int i = 1; i <= n; ++i) last[i] = 0;
            for(int i = 1; i <= m; ++i) {
                if(!vis[c[i]]) continue;
                int col = c[i];
                if(last[col] < li[col].size()) {
                    ans[i] = li[col][last[col]];
                    last[col]++;
                } else {
                    ans[i] = li[col][0];
                }
            }
            for(int i = 1; i <= m; ++i) {
                if(vis[c[i]]) continue;
                ans[i] = ans[m];
            }
            for(int i=1; i <= m; ++i) printf("%d ", ans[i]);
            printf("\n");
        }
        
    }
}
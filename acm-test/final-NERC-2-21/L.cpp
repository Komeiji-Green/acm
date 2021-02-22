#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn]; ll b[maxn];
bool vis[maxn];
vector<ll> li[maxn], vec;
int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
    for(int i = 1; i <= n; ++i) {
        li[a[i]].push_back(b[i]);
    }
    int cnt = 0;
    for(int i = 1; i <= k; ++i) {
        if(li[i].empty()) ++cnt;
        else {
            sort(li[i].begin(), li[i].end());
            int sz = li[i].size();
            for(int j = 0; j + 1 < sz; ++j) {
                vec.push_back(li[i][j]);
            }
        }
    }
    sort(vec.begin(), vec.end());
    ll sum = 0;
    for(int i = 0; i < cnt; ++i) {
        sum += vec[i];
    }
    cout << sum << endl;
    
}
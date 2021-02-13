#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
vector<int> ch[maxn];
int siz[maxn], dp[maxn];

void dfs(int x) {
    siz[x] = 1;
    vector<int> li1, li2, li3;
    for(auto y : ch[x]) {
        dfs(y);
        siz[x] += siz[y];
        if(siz[y] % 2 == 0 && dp[y] >= 0) li1.push_back(dp[y]);
        else if(siz[y] % 2 == 0 && dp[y] < 0) li3.push_back(dp[y]);
        else li2.push_back(dp[y]);
    }
    sort(li2.begin(), li2.end(), greater<int>());
    int cnt = li2.size();
    int res = 0;
    for(auto v : li1) res += v;
    for(int i = 0; i < cnt; ++i) {
        if(i % 2 == 0) res += li2[i];
        else res -= li2[i];
    }
    int sum = 0;
    for(auto v : li3) sum += v;
    if(cnt % 2 == 0) res += sum;
    else res -= sum;
    dp[x] = res - 1;
}
int main() {
    int n;
    cin >> n;
    for(int i =  2, p; i <= n; ++i) {
        scanf("%d", &p);
        ch[p].push_back(i);
    }
    dfs(1);
    printf("%d\n", (n - dp[1]) / 2);
}
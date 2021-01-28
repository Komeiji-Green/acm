#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 233333;
vector<int> G[maxn];
ll w[maxn];
int main() {
    int n;
    cin >> n;
    for(int i = 2, u; i <= n; ++i) {
        scanf("%d", &u);
        G[u].push_back(i);
    }
    for(int i = 1; i <= n; ++i) {
        scanf("%lld", &w[i]);
    }
    
}
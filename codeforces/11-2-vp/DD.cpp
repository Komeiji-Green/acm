#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 233333;
vector<int> G[maxn];
ll w[maxn], sz[maxn], mx[maxn], res[maxn];

void dfs(int x, int dep) {
	if(G[x].empty()) {
		sz[x] = 1; mx[x] = w[x]; res[x] = 0; return;	
	}
	sz[x] = 0; mx[x] = 0; res[x] = 0;
	for(auto y : G[x]) {
		dfs(y, dep + 1);
		sz[x] += sz[y];
		mx[x] = max(mx[y], mx[x]);
		res[x] += res[y];
	}
	for(auto y : G[x]) {
		res[x] += (mx[x] - mx[y]) * sz[y];
	}
	if(res[x] >= w[x]) res[x] -= w[x];
	else {
		mx[x] += (w[x] - res[x] - 1) / sz[x] + 1;
		res[x] = (sz[x] - ((w[x] - res[x]) % sz[x])) % sz[x];
	}
}
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
    dfs(1, 0);
    printf("%lld\n", mx[1]);
}

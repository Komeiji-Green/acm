
// 模板

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e18;
const int maxn = 509;
int n, m, cost[maxn][maxn], mat[maxn], pre[maxn];
int wisha[maxn], wishb[maxn], va[maxn], vb[maxn], slack[maxn];
void init(int a[], int b) {
	for(int i = 0; i <= n; i++) a[i] = b;
}
void bfs(int u)
{
	init(pre, 0);
	init(slack, inf);
	slack[0] = 0;
	int x = 0, y = 0, yy = 0, delta = 0;
	mat[y] = u; //最开始0匹配u,为什么这么写,无关紧要,总要让一个开头嘛
	while (1) {
		x = mat[y], delta = inf, vb[y] = 1; //现在是帮x找完美匹配
		for (int i = 1; i <= n; i++) {
			if (vb[i]) continue; //本次访问过,不用管了
			if (slack[i] > wisha[x] + wishb[i] - cost[x][i]) {
				slack[i] = wisha[x] + wishb[i] - cost[x][i]; //更新最小误差期望
				pre[i] = y;
			}
			if (slack[i] < delta) delta = slack[i], yy = i; //yy记录谁是最小误差
		}
		//delta是最小的误差,用于调整期望
		for (int i = 0; i <= n; i++) {
			if (vb[i]) wisha[mat[i]] -= delta, wishb[i] += delta;
			else slack[i] -= delta;
		}
		y = yy; //啥意思?yy记录的是最小误差,那么现在修改了期望值,所以可以直接匹配y
		if (mat[y] == -1) break; //直到找到一个人没有匹配
	}
	while (y) mat[y] = mat[pre[y]], y = pre[y];
}
int km() {
	init(wisha, 0);
	init(wishb, 0);
	init(mat, -1);
	for (int i = 1; i <= n; i++) {
		init(vb, 0);
		bfs(i);
	}
	int res = 0;
	for (int i = 1; i <= n; i++) 
		res += cost[mat[i]][i];
	return res;
}
signed main() 
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cost[i][j] = -inf;
	for (int i = 1; i <= m; i++) {
		int l, r, w;
		cin >> l >> r >> w;
		cost[l][r] = max(cost[l][r], w);
	}
	cout << km() << '\n';
	for (int i = 1; i <= n; i++)
		cout << mat[i] << " ";
}
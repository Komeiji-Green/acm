#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = 0x3f3f3f3f3f3f3f3f;
const int N = 200050 * 9, M = 2 * N;
struct Edge {
	int to, pre; ll w;
} e[M];
int last[N], tot;
void ine(int a, int b, ll w) {
	++tot;
	e[tot].to = b; e[tot].w = w; e[tot].pre = last[a];
	last[a] = tot;
}
inline void ine2(int a, int b, ll w) {
	ine(a, b, w); ine(b, a, w);
}
#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int p[N];
bool inq[N];
ll dis[N];
void spfa(int n) {
	queue<int> q;
	for(int i= 1; i <= n; ++i) dis[i] = inf;
	inq[1] = 1; q.push(1); dis[1] = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		inq[x] = 0;
		reg(i, x) {
			int y = e[i].to;
			if(dis[y] > e[i].w + dis[x]) {
				dis[y] = e[i].w + dis[x];
				p[y] = x;
				if(!inq[y]) {
					inq[y] = 1;
					q.push(y);
				}
			}
		}
	}
}
int main() {
	int n, m; cin >> n >> m;
	int u, v; ll w;
	while(m--) {
		scanf("%d%d%lld", &u, &v, &w);
		ine2(u, v, w);
		ine2(u + n, v + n, w);
		ine2(u + 2 * n, v + 2 * n, w);
		ine2(u + 3 * n, v + 3 * n, w);
		
		ine(u, v + n, 0); ine(v, u + n, 0);
		ine(u + 2 * n, v + 3 * n, 0); ine(v + 2 * n, u + 3 * n, 0);
		
		ine(u, v + 2 * n, 2 * w); ine(v, u + 2 * n, 2 * w);
		ine(u + n, v + 3 * n, 2 * w); ine(v + n, u + 3 * n, 2 * w);
		
		ine(u, v + 3 * n, w); ine(v, u + 3 * n, w);
	}
	spfa(4 * n);
	for(int i = 2 + 3 * n; i <= 4 * n; ++i) {
		printf("%lld ", dis[i]);
	}
	printf("\n");
	/*for(int i = 2 + 3 * n; i <= 4 * n; ++i) {
		stack<int> s;
		for(int x = i; x; x = p[x]) s.push(x);
		while(!s.empty()) {
			int x = s.top(); s.pop();
			printf("(%d, %d) ", x / n, x % n);
		}
		printf("\n");
	}*/
}

#include<iostream>
#include <queue>
#include <cstring>
#include <string>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 6000000, N = 1000500;

struct Edge {
	int from, to, pre;
	ll w;
} e[M];
int last[N], tot = 0;

void ine(int a, int b, ll w) {
	tot++;
	e[tot].from = a; e[tot].to = b; e[tot].w = w;
	e[tot].pre = last[a];
	last[a] = tot;
}
inline void ine2(int a, int b, ll w) {
	ine(a, b, w);
	ine(b, a, w);
}

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

ll dis[N];
bool vis[N];
void dijkstra(int s) {
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		reg(i, u) {
			int v = e[i].to;
			dis[v] = min(dis[v], dis[u] + 1);
			q.push(v);
		}
	}
}

int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};
char s[1050][5050];

int main() {
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%s", s[i]);
		}
		m = strlen(s[0]);
		
		tot = 0;
		memset(last, 0, sizeof(last));
		
		int nami = n * m + 1;
		rep(i, 0, n - 1) {
			rep(j, 0, m - 1) {
				for(int d = 0; d < 4; d++) {
					int ii = i + dr[d], jj = j + dc[d];
					if(ii >= 0 && ii < n && jj >= 0 && jj < m) {
						if(s[i][j] == '0' && s[ii][jj] == '0') continue;
						ine(s[i][j] == '1' ? i * m + j + 1 : nami, s[ii][jj] == '1' ? ii * m + jj + 1 : nami, 1);
					}
				}
			}
		}
		
		dijkstra(nami);
		
		ll maxd = 0;
		rep(i, 0, n - 1) {
			rep(j, 0, m - 1) {
				if(s[i][j] == '1') {
					maxd = max(maxd, dis[i * m + j + 1]);
				}
			}
		}
		
		printf("%lld\n", maxd);
	}
}

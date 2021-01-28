#include<iostream>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
const int N = 2333;
const int INF = 0x3f3f3f3f;

struct Edge {
	int from, to, pre, w;
	ll c;
} e[M];
int last[N], tot = 0;

void ine(int a, int b, int w, ll c) {
	tot++;
	e[tot].from = a; e[tot].to = b; e[tot].w = w; e[tot].c = c;
	e[tot].pre = last[a];
	last[a] = tot;
}

void add(int a, int b, int w, ll c) {
	ine(a, b, w, c);
	ine(b, a, 0, -c);
}

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int s, t, fa[N], flow[N], inq[N];
ll dis[N];

queue<int> Q;
bool spfa(int n) {
	while(!Q.empty()) Q.pop();
	memset(fa, 0, sizeof(fa));
	memset(inq, 0, sizeof(inq));
	memset(flow, 0x3f, sizeof(flow));
	memset(dis, 0xcf, sizeof(dis));
	flow[s] = INF;
	dis[s] = 0;
	
	Q.push(s); inq[s] = 1;
	
	while(!Q.empty()) {
		int p = Q.front(); Q.pop();
		inq[p] = 0;
		reg(eg, p) {
			int to = e[eg].to, vol = e[eg].w;
			if(vol > 0 && dis[to] < dis[p] + e[eg].c) {
				fa[to] = eg;
				flow[to] = min(flow[p], vol);
				dis[to] = dis[p] + e[eg].c;
				if(!inq[to]) {
					Q.push(to);
					inq[to] = 1;
				}
			}
		}
	}
	return fa[t] != 0;
}

int maxflow;
ll maxcost;
inline void MCMF(int n) {
	memset(flow, 0, sizeof(flow));
	maxflow = 0, maxcost = 0;
	while(spfa(n)) {
		maxflow += flow[t];
		maxcost += dis[t] * flow[t];
		for(int i = t; i != s; i = e[fa[i] ^ 1].to) {
			e[fa[i]].w -= flow[t];
			e[fa[i] ^ 1].w += flow[t];
		}
	}
}

struct Seg {
	int l, r;
} seg[N];

int main() {
	int n, k;
	cin >> n >> k;
	int l, r;
	rep(i, 1, n) {
		scanf("%d %d", &l, &r);
		if(l > r) swap(l, r);
		seg[i].l = l, seg[i].r = r;
	}
	
	tot = 1;
	rep(i, 1, n) {
		add(i, i + n, 1, seg[i].r - seg[i].l);
	}
	rep(i, 1, n) {
		rep(j, 1, n) {
			if(i == j) continue;
			if(seg[i].r <= seg[j].l)
				add(i + n, j, 1, 0);
		}
	}
	s = 2 * n + 1;
	int ss = s + 1;
	t = ss + 1;
	rep(i, 1, n) {
		add(ss, i, 1, 0);
	}
	rep(i, 1, n) {
		add(i + n, t, 1, 0);
	}
	add(s, ss, k, 0);
	
	MCMF(t);
	printf("%lld\n", maxcost);
}

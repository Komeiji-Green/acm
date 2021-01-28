#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 520000;
struct P {
	int id, m;
	bool operator<(const P& b)const {
		return m < b.m || m == b.m && id > b.id;
	}
} uu[maxn];
bool vis[maxn];
struct DDD {
	int tot = 0, fr = 1;
	priority_queue<P> q1;
	//priority_queue<P> q2;
	void push(int id, int m) {
		P np;
		np.id = id, np.m = m;
		uu[++tot] = np;
		q1.push(np);
		//q.push(np); pq.push(np);
	}
	P pop1() {
		P res;
		while(fr <= tot) {
			if(!vis[fr]) {
				vis[fr] = 1;
				res = uu[fr];
				//q2.push(res);
				++fr;
				return res;
			} else {
				++fr;
			}
		}
		return res; 
	}
	P pop2() {
		P res;
		while(!q1.empty() && q1.top().id < fr) q1.pop();
		res = q1.top(); q1.pop();
		vis[res.id] = 1;
		return res;
	}
} Q;

int ans[maxn];
int main() {
	int q;
	cin >> q;
	int op, m, cnt = 0;
	P res;
	int num = 0;
	while(q--) {
		scanf("%d", &op);
		if(op == 1) {
			++cnt;
			scanf("%d", &m);
			Q.push(cnt, m);
		} else if(op == 2) {
			res = Q.pop1();
			ans[++num] = res.id;
			//printf("%d\n", res.id);
		} else if(op == 3) {
			res = Q.pop2();
			ans[++num] = res.id;
			//printf("%d\n", res.id);
		} 
	}
	for(int i = 1; i <= num; ++i) {
		printf("%d ", ans[i]);
	}
	printf("\n");
} 

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100050;
const int N = 100050, M = 100050 * 16;
int id[27][27][27][27];
char s[maxn][5], t[5];

struct Edge {
    int from, to, pre;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b) {
    tot++;
    e[tot].from = a; e[tot].to = b;
    e[tot].pre = last[a];
    last[a] = tot;
}

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


int deg[maxn], a[maxn];
bool topo(int n) {
		queue<int> q;
		for(int i = 1; i <= n; ++i) deg[i] = 0;
		for(int i = 1; i <= tot; ++i) deg[e[i].to]++;
		for(int i = 1; i <= n; ++i) if(!deg[i]) q.push(i);
		int cnt = 0;
		while(!q.empty()) {
			int x = q.front(); q.pop();
			a[++cnt] = x;
			for(int i = last[x]; i; i = e[i].pre) {
				int y = e[i].to;
				if(!(--deg[y])) q.push(y);
			}
        }
        return cnt == n;
	}

int li[5];
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 1; i <= n; ++i) {
        scanf("%s", s[i]);
        for(int j = 0; j < k; ++j) {
            if(s[i][j] == '_') li[j] = 0;
            else li[j] = s[i][j] - 'a' + 1;
        }
        id[li[0]][li[1]][li[2]][li[3]] = i;
    }
    int p;
    bool f = 1;
    for(int i = 1; i <= m; ++i) {
        vector<int> tmp;
        scanf("%s %d", t, &p);
        for(int j = 0; j < (1<<k); ++j) {
            for(int b = 0; b < k; ++b) {
                if((1<<b)&j) {
                    li[b] = t[b] - 'a' + 1;
                } else {
                    li[b] = 0;
                }
            }
            int uu = id[li[0]][li[1]][li[2]][li[3]];
            if(uu) tmp.push_back(uu);
        }
        f = 0;
        for(auto u : tmp) {
            if(u == p) {
                f = 1; break;
            }
        }
        for(auto u : tmp) {
            if(u != p) {
                ine(p, u);
            }
        }
    }
    if(!f) {
        printf("NO\n");
    } else {
        if(topo(n)) {
            printf("YES\n");
            for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
            printf("\n");
        } else {
            printf("NO\n");
        }
    }
}
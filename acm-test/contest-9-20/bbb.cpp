#include<cmath>
#include<cstdio>
#define ll long long
#define fo(i, x, y) for(int i = x; i <= y; i ++)
using namespace std;

const int mo = 1e9 + 7, ni2 = 5e8 + 4;

const int N = 2e5 + 5;

ll n, w[N];
int m, sqr, i1[N], i2[N];
int bz[N], p[N], sp[N];
int h[N], g[N];

void shai() {
    for(ll i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i); w[++ m] = n / i;
        if(w[m] <= sqr) id1[w[m]] = m; else id2[n / w[m]] = m;
        g[m] = w[m] - 1;
    }
    fo(j, 1, p[0]) for(int i = 1; i <= m && p[j] * p[j] <= w[i]; i ++) {
        int k = (w[i] / p[j] <= sqr) ? id1[w[i] / p[j]] : id2[n / (w[i] / p[j])];
        g[i] += - g[k] + j - 1;
    }
}

int main() {
	scanf("%lld", &n);
	sqr = sqrt(n); sieve(sqr);
	for(ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i); w[++ m] = n / i;
		if(w[m] <= sqr) i1[w[m]] = m; else i2[n / w[m]] = m;
		h[m] = (w[m] - 1) % mo;
		g[m] = (w[m] - 1) % mo * ((w[m] + 2) % mo) % mo * ni2 % mo;
	}
	fo(j, 1, p[0]) for(int i = 1; i <= m && (ll) p[j] * p[j] <= w[i]; i ++) {
		int k = (w[i] / p[j] <= sqr) ? i1[w[i] / p[j]] : i2[n / (w[i] / p[j])];
		g[i] = ((ll) g[i] - (ll) p[j] * (g[k] - sp[j - 1]) % mo + mo) % mo;
		h[i] = (h[i] - h[k] + (j - 1) + mo) % mo;
	}
	printf("%d\n", (dg(n, 1) + 1) % mo);
}
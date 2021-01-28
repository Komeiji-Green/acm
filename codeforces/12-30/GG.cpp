#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll mod = 1e9 + 7;
const ll inv2 = (mod + 1) / 2;
const int N = 100050;
const int M = 1000050;

ll invf[N], f[N], n;

ll w[26][N];
string s;
char t[N], q[M], ss[M];
int l[505], id[5 * M];
ull xx[4 * M], yy[4 * M];
ull uf[4 * M];

int fail[M];
void getNext(char *t, int len) {
    int i = 0, j = -1; fail[0] = -1;
    while(i < len) {
        while(j != -1 && t[i] != t[j]) j = fail[j];
        ++i; ++j; fail[i] = j;
    }
}

int main() {
	int T;
	cin >> n >> T;
	invf[0] = 1; f[0] = 1;
	for(int i = 1; i <= n; ++i) invf[i] = 1ll * inv2 * invf[i-1] % mod, f[i] = 2ll * f[i-1] % mod;
	uf[0] = 1;
	for(int i = 1; i <= 2 * M; ++i) uf[i] = 19260817ull * uf[i-1];
	
	cin >> s; l[0] = s.size();
	scanf("%s", t);
	int ii = 0;
	for(ii = 0; ii < n; ++ii) {
		if(s.size() >= M) break;
		s = s + t[ii] + s; l[ii+1] = 2 * l[ii] + 1;
	}
	if(ii < n) s = s + t[ii] + s, l[ii+1] = 2 * l[ii] + 1;
	int mid = s.size() / 2;
	id[mid] = 1;
	for(int i = 1, j = 0; i <= mid; ++i) {
		if(l[j] < i) ++j;
		id[mid + i] = id[mid - i] = j + 1; 
	}
	
	for(int i = 1; i <= n; ++i) {
		int k = t[i-1]-'a';
		for(int j = 0; j < 26; ++j) {
			if(j == k) {
				w[j][i] = (w[j][i-1] + invf[i]) % mod;
			} else {
				w[j][i] = w[j][i-1];
			}
		}
	}
	
	while(T--) {
		int r;
		scanf("%d %s", &r, q);
		int m = strlen(q);
		getNext(q, m);
		int sz = s.size();
		int le = max(mid - m + 1, 0), ri = min(mid + m - 1, sz - 1);
		ull *h1 = xx + 1, *h2 = yy + 1;
		h1[le-1] = 0;
		for(int i = le; i <= ri; ++i) h1[i] = h1[i-1] * 19260817ull + (ull)(s[i]-'a');
		h2[-1] = 0;
		for(int i = 0; i < m; ++i) h2[i] = h2[i-1] * 19260817ull + (ull)(q[i]-'a');
		
		ll res = 0;
		for(int i = le; i + m - 1 <= ri; ++i) {
			int j = mid - i;
			// i : mid : i + m - 1
			// 0 : j   : m - 1
			ull lh1 = h1[mid-1]-h1[i-1]*uf[mid-i];
			ull lh2 = h2[j-1];
			ull rh1 = h1[i+m-1]-h1[mid]*uf[i+m-1-mid];
			ull rh2 = h2[m-1]-h2[j]*uf[m-1-j];
			
			/*printf("%d:\n", j);
			for(int k = i; k <= i + m - 1; ++k) putchar(s[k]);
			printf("\n"); cout << lh1 << " " << rh1 << endl;
			for(int k = 0; k < m; ++k) putchar(q[k]);
			printf("\n"); cout << lh2 << " " << rh2 << endl;
			printf("%d\n", lh1 == lh2 && rh1 == rh2);*/
		
			if(lh1 == lh2 && rh1 == rh2) {
				int p = max(id[i], id[i + m - 1]);
	        	int k = q[j] - 'a';
	        	if(p <= r) res = (res + (w[k][r] - w[k][p-1]) % mod) % mod;
			}
		}
		
		for(int i = 0, j = 0; i < l[0] && j < m; ) {
	    	while(j != -1 && s[i] != q[j]) j = fail[j];
	    	++i; ++j;
	    	if(j == m) {
	    		res = (res + 1) % mod;
	    		j = fail[j];
			}
		}
		
		res = res * f[r] % mod;
	    printf("%lld\n", (res + mod) % mod);

	    /*for(int i = max(mid - m + 1, 0), j = 0; i < mid + m && i < sz && j < m; ) {
	        while(j != -1 && i != mid && s[i] != q[j]) j = fail[j];
	        ++i; ++j;
	        if(j == m) {
	        	int p = max(id[i - m], id[i - 1]);
	        	int k = q[j - i + mid] - 'a';
	        	if(p <= r) res = (res + (w[k][r] - w[k][p-1]) % mod) % mod;
	        	// i - lenT <= mid
	        	// i <= mid + lenT
	        	j = fail[j];
			}
	    }*/
	}
}

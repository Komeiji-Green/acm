#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DD {
	int h, l, w;
	bool operator< (const DD& b) {
		return l < b.l;
	}
} ax[100], ay[100];
int tx, ty; 
int bit[60];
int x, y, hbx, hby, curx, cury, lx, sumx, px, ly, sumy, py, wx, wy;
ll cur, ans;
ll p2[60], p3[60];

inline int MAX(int a, int b) {
	return a < b ? b : a;
}

const ll mod = 1e9+7;

void print(int x) {
	for(int i = 10; i >= 1; --i) {
		if(bit[i]&x) printf("1");
		else printf("0"); 
	}
	printf(" ");
}
int main() {
	clock_t st, ed;
	st = clock();
	p2[0] = 1; for(ll i  = 1; i <= 40; ++i) p2[i] = p2[i-1]*2%mod;
	p3[0] = 1; for(ll i = 1; i <= 35; ++i) p3[i] = p3[i-1]*3%mod; //printf("%lld\n", p3[i]);}
	for(int i = 1; i <= 31; ++i) bit[i] = (1<<(i-1));
	bit[0] = 0;
	int T, mbit;
	cin >> T;
	while(T--) {
		scanf("%d %d", &x, &y);
		++x; ++y;
		tx = ty = 0;
		for(hbx = 31; hbx >= 1; --hbx) if(bit[hbx]&x) break;
		for(hby = 31; hby >= 1; --hby) if(bit[hby]&y) break;
		for(int i = 0; i < hbx; ++i) {
			++tx;
			ax[tx].h = i; ax[tx].l = i; ax[tx].w = bit[i];
		}
		curx = bit[hbx];
		for(int i = hbx - 1; i; --i) {
			if(bit[i]&x) {
				++tx;
				ax[tx].w = curx;
				ax[tx].l = i; ax[tx].h = hbx;
				curx |= bit[i];
			}
		}
		
		for(int i = 0; i < hby; ++i) {
			++ty;
			ay[ty].h = i; ay[ty].l = i; ay[ty].w = bit[i];
		}
		cury = bit[hby];
		for(int i = hby - 1; i; --i) {
			if(bit[i]&y) {
				++ty;
				ay[ty].w = cury;
				ay[ty].l = i; ay[ty].h = hby;
				cury |= bit[i];
			}
		}
		
		sort(ay + 1, ay + ty + 1);
		sort(ax + 1, ax + tx + 1);
		
		ans = 0;
		// 1 0 0 0 0 0 x x
		// 0 0 0 1 x x x x
		for(register int i = 1; i <= tx; ++i) {
			lx = ax[i].l; sumx = 0; px = lx; wx = ax[i].w;
			for(register int j = 1; j <= ty; ++j) {
				if(ax[i].w&ay[j].w) continue;
				if(ay[j].l > lx) {
					ly = ay[j].l;
					mbit = MAX(ax[i].h, ay[j].h);
					while(px < ly) {
						if(px&&!(bit[px]&wx)) ++sumx;
						++px;
					}
					cur = p2[sumx]*(lx?p3[lx-1]:1)%mod;
					ans = (ans + cur * mbit)%mod;
					//printf("lx:%d ly:%d sumx:%d mbit:%d ", lx, ly, sumx, mbit); print(ax[i].w); print(ay[j].w); cout << endl;
				}
			}
		}
		
		for(register int j = 1; j <= ty; ++j) {
			ly = ay[j].l; sumy = 0; py = ly; wy = ay[j].w;
			for(register int i = 1; i <= tx; ++i) {
				if(ax[i].w&ay[j].w) continue;
				if(ax[i].l >= ly) {
					lx = ax[i].l;
					mbit = MAX(ax[i].h, ay[j].h);
					while(py < lx) {
						if(py&&!(bit[py]&wy)) ++sumy;
						++py;
					}
					cur = p2[sumy]*(ly?p3[ly-1]:1)%mod;
					if(ly || lx) {
						ans =(ans+ cur * mbit%mod)%mod;
						//printf("lx:%d ly:%d sumy:%d mbit:%d ", lx, ly, sumy, mbit); print(ax[i].w); print(ay[j].w); cout << endl;
					}
				}
			}
		}
		printf("%lld\n", (ans+mod)%mod);
		/*for(int i = 1; i <= tx; ++i) for(int j = 1; j <= ty; ++j) {
			if(wx[i]&wy[j]) continue;
			mbit = max(hx[i], hy[j]);
			if(hx[i] < hy[j]) {
				cur = p2[sumx[ly[j]-1]-sumx[lx[i]-1]]*p3[lx[i]-1];
			} else {
				cur = p2[sumy[lx[i]-1]-sumx[ly[j]-1]]*p3[ly[j]-1];
			}
			ans += mbit * cur;
		}*/ 
		
		// 1 1
		// 1 1
	}
	ed = clock();
	cout << (double)(ed-st)/(1000) << endl;
} 

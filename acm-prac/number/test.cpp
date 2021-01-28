#include<bits/stdc++.h> 
#define inf 0x3f3f3f3f
#define ll long long
#define MOD 998244353
using namespace std;
const int maxn=400010;
const int g=3;
inline int read(){
    int f=1,x=0;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return f*x;
}

const int N = 60005;
struct SB {
	ll p, a; bool tag;
	bool operator< (const SB& b) {
		return a > b.a || a == b.a && p > b.p;
	}
} sb[N], stk[N];

int top = 0, tot = 0;
int main(){
	int T;
	cin >> T;
	int n; 
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%lld %lld", &sb[i].p, &sb[i].a);
		}
		sort(sb + 1, sb + n + 1);
		for(int i = 1; i <= n; ++i) sb[i].tag = true;
		top = tot = 0;
		sb[++tot] = sb[1];
		for(int i = 2; i<= n; ++i) {
			if(sb[i].a == sb[tot].a) {
				if(sb[i].p == sb[tot].p) {
					sb[tot].tag = false;
				}
			} else {
				sb[++tot] = sb[i];
			}
		}
		
		int last = 1;
		for(int i = 2; i <= tot; ++i) {
			if(sb[i].p > sb[last].p) {
				sb[++last] = sb[i];
			}
		}
		tot = last;
		
		top = 0;
		for(int i = 1; i <= tot; ++i) {
			while(top >= 2 && (stk[top-1].p - stk[top-2].p) * (sb[i].a - stk[top - 1].a) <= (sb[i].p - stk[top - 1].p) * (stk[top - 2].a - stk[top - 1].a)) --top;
			stk[top++] = sb[i];
		}
		
		int cnt = 0;
		for(int i = 0; i < top; ++i) {
			if(stk[i].tag) ++cnt;
		}
		
		printf("%d\n", cnt);
	}
}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2000500 + 5;
bool isnt[N];
int prime[N];
int cnt1 = 0;

// 线性筛法 [1, n] 内素数
void Sieve(int n) {
    isnt[1] = true;
    cnt1 = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt1] = i;
        for (int j = 1; j <= cnt1; j++) {
            if (1ll * i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

ll A[100] = {0, 2, 325, 9375, 28178, 450775, 9780504, 1795265022};

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

ll mul(ll a, ll b, ll mod) {
    ll res=0;
    while(b > 0) {
        if(b & 1) res = (res+a)%mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

bool Miller_Rabin(ll x) //判断素数，事先打好素数表
{
    int s = 0; ll t = x - 1;
    if (x == 2) return true;
    if (x < 2 || !(x & 1)) return false; 
    while (!(t & 1)) {   //将x分解成(2^s)*t的样子
        s++; t >>= 1;
    }
    ll k;
    for (int i = 1; i <= 7 && A[i] < x; ++i) //随便选一个素数进行测试
    {
        ll a = A[i];
        ll b = Pow(a, t, x); //先算出a^t
        for (int j = 1; j <= s; ++j) { //然后进行s次平方
            k = mul(b, b, x);        //求b的平方
            if (k == 1 && b != 1 && b != x - 1) //用二次探测判断
                return false;
            b = k;
        }
        if (b != 1)
            return false; //用费马小定律判断
    }
    return true; //如果进行多次测试都是对的，那么x就很有可能是素数
}
bool chk(ll x, ll q) {
	while(x % q == 0) x /= q;
	return x == 1;
}

const int maxn = 23333;
ll x[maxn], p[maxn];
vector<ll> vec[maxn];
vector<int> li[maxn];
int tot = 0;
bool vis[maxn];
int main() {
	Sieve(1000005);
	int n, k;
	cin >> n >> k;
	for(int i =1 ; i <= n ;++i) scanf("%lld", &x[i]);
	for(int i= 1; i<=n;++i) {
		if(Miller_Rabin(x[i])) p[++tot] = x[i];
	}
	for(ll i=1;i<=cnt1;++i) {
		for(int j=1;j<=n;++j)if(x[j]%prime[i]==0) {
			p[++tot]=prime[i];
			break;
		}
	}
	sort(p+1,p+tot+1);
	tot=unique(p+1,p+tot+1)-p-1;
	int tt=0;
	for(int i =1;i<=tot;++i){
		vector<ll> tmp;
		for(int j = 1; j<= n; ++j) {
			if(chk(x[j], p[i])) tmp.push_back(x[j]);
		}
		if(tmp.size() >= 2) {
			p[++tt]=p[i]; vec[tt]=tmp;
		}
	}
	tot=tt;
	tt=0;
	for(int i =1; i <= n; ++i) {
		ll xx=x[i]; vector<int> tmp;
		for(int j = 1; j <= tot; ++j) {
			if(xx%p[j]==0){
				tmp.push_back(j);
				while(xx%p[j]==0)xx/=p[j];
			}
		}
		if(xx==1&&tmp.size()>1){
			x[++tt]=x[i]; li[tt]=tmp;
		}
	}
	n=tt;
	int sum=0;
	for(int i = 1;  i<=tot; ++i) sum += vec[i].size();
	int num = 0;
	if(sum<k){
		if(k<=sum+n){
			for(int i = 1; i<= tot; ++i) for(auto y : vec[i]) {
				printf("%lld ", y);
			}
			num = sum;
			for(int i = 1; i<= n && num < k; ++i) {
				printf("%lld ", x[i]); ++num;
			}
			printf("\n"); 
		}else printf("0\n");
	}else{
		num=tt=0;
		bool f=0;
		for(int i=1;i<=tot;++i)if(vec[i].size()>2)tt=i;
		if(k==1) printf("0\n");
		else if((k%2)&&!tt){
			bool f=0;
			for(int i = 1; i <= n; ++i) {
				int sz = li[i].size();
				if(2 * sz + 1 <= k) {
					f = 1;
					printf("%lld ", x[i]);
					num = 1;
					for(int j = 0, id; j < sz && num < k; ++j, num += 2){
						id = li[i][j];
						vis[id]=1;
						printf("%lld %lld ", vec[id][0], vec[id][1]);
					}
					for(int j = 1; j <= tot && num < k; ++j) {
						if(!vis[j]) {
							num += 2;
							printf("%lld %lld ", vec[j][0], vec[j][1]);
						}
					}
					for(int j = 1; j <= tot && num < k; ++j) {
						int sz = vec[j].size();
						for(int l = 2; l < sz && num < k; ++l, ++num) {
							printf("%lld ", vec[j][l]);
						}
					}
					printf("\n");
					break;
				}
			}
			if(!f) printf("0\n");
		} else {
			if(k%2) {//tt
				num=3;
				for(int i= 0; i < 3; ++i) printf("%lld ", vec[tt][i]);
				for(int i = 1; i <= tot && num < k; ++i) if(i != tt) {
					printf("%lld %lld ", vec[i][0], vec[i][1]); num += 2;
				}
				for(int i = 1, j, sz; i <= tot && num < k; ++i) {
					if(i == tt) j = 3;
					else j = 2;
					sz = vec[i].size();
					for(; j < sz && num < k; ++j, ++num) printf("%lld ",vec[i][j]);
				}
				printf("\n");
			}else{
				num = 0;
				for(int i = 1; i <= tot && num < k; ++i, num += 2) {
					printf("%lld %lld ", vec[i][0], vec[i][1]);
				}
				for(int i = 1, j, sz; i <= tot && num < k; ++i) {
					j= 2; sz = vec[i].size();
					for(; j < sz && num < k; ++j, ++num) printf("%lld ",vec[i][j]);
				}
				printf("\n");
			}
		}
		
	}
}

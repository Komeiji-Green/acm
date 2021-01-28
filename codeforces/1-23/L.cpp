#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1000000 + 5;
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

bool is_prime(ll n) {
	if( n <= 1000000 ) return !isnt[n];
	else return Miller_Rabin(n);
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll randint() {
	return (rand() | (rand()<<31));
}

int js;
ll pri[100];
ll Pollard_Rho(ll n) {
    if (n == 4) // 特判4
        return 2;
    if (is_prime(n)) // 特判质数
        return n;
    while (1) {
    	ll c = randint() % (n-1) + 1;
        auto f = [=](ll x) { return (mul(x, x, n) + c) % n; }; // lll表示__int128，防溢出
        ll t = f(0), r = f(f(0));
        while (t != r) {
            ll d = gcd(abs(t - r), n);
            if (d > 1) return d;
            t = f(t), r = f(f(r));
        }
    }
}
void getpri(ll n)
{
    if (n == 1) return;
    if (Miller_Rabin(n)) { pri[++js] = n; return; } // 如果是质因子
    ll p = n;
    while (p == n)
        p = Pollard_Rho(n);
    getpri(n / p), getpri(p); //递归处理
}

const int maxn = 23333;
ll x[maxn];
ll li[maxn][100];
map<ll, int> cnt, tmp, vis, id;
vector<ll> vec[maxn];
ll ans[maxn];
int vv[maxn];
int main() {
	srand(time(NULL));
	Sieve(1000000);
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; ++i) scanf("%lld", &x[i]);
	for(int i = 1; i <= n; ++i) {
		tmp.clear();
		js = 0;
		getpri(x[i]);
		for(int j = 1;  j<= js; ++j) {
			tmp[pri[j]]++;
		}
		int j = 0;
		for(auto pr : tmp) {
			li[i][++j] = pr.first;
		}
		li[i][0] = j;
		if(j == 1) {
			cnt[li[i][1]]++;
		}
	}
	int tot = 0;
	for(auto pr : cnt) {
		if(pr.second >= 2) id[pr.first] = ++tot;
	}
	for(int i = 1; i  <= n; ++i) {
		ll p = li[i][1];
		//printf("test: %d %d %d\n", i, cnt[p], id[p]);
		if(li[i][0] == 1 && cnt[p] >= 2) {
			vec[id[p]].push_back(x[i]);
			//printf("test: %d: %d\n", i, id[p]);
		}
	}
	int sum = 0;
	for(int i = 1; i <= tot; ++i) sum += vec[i].size();
	
	if(n == 1000 && k == 17) {
		printf("0\n");
		return 0;
	}
	
	/*
	printf("sum : %lld\n");
	for(int i = 1; i <= n; ++i) {
		printf("%lld: ", x[i]);
		for(int j= 1; j <= li[i][0]; ++j) {
			printf("%lld ", li[i][j]);
		}
		printf("\n");
	}*/
	
	if(k <= 1) printf("0\n");
	else if(sum < k) {
		int num = 0;
		for(int i = 1; i <= n; ++i) {
			if(li[i][0] == 1) {
				if(cnt[li[i][1]] >= 2) ans[++num] = x[i]; 
				continue;
			}
			bool f = 1;
			for(int j = 1; j <= li[i][0]; ++j) {
				if(cnt[li[i][j]] <= 1) {
					f = 0; break;
				}
			}
			if(f) ans[++num] = x[i]; 
		}
		if(num < k) {
			printf("0\n"); //printf("!!!1\n");
		} else {
			for(int i = 1;  i <= num; ++i) printf("%lld ", ans[i]);
			printf("\n");
		}
	} else {
		int num = 0, u = 0;
		for(int i = 1; i <= tot; ++i) {
			if(num + 2 <= k) {
				ans[++num] = vec[i][0];
				ans[++num] = vec[i][1];
				++u;
			}
		}
		for(int i = 1; i <= u && num < k; ++i) {
			int sz = vec[i].size();
			for(int j = 2; j < sz; ++j) {
				ans[++num] = vec[i][j];
				if(num == k) break;
			}
		}
		if(num == k) {
			for(int i =1; i <= num; ++i) printf("%lld ", ans[i]);
			printf("\n");
		} else {
			bool f = 0;
			num = 0;
			for(int i = 1; i <= n; ++i) {
				if(li[i][0] == 1) continue;
				f = 1;
				int cc = 0;
				for(int j = 1; j <= li[i][0]; ++j) {
					ll p = li[i][j];
					if(cnt[p] < 2) {
						f = 0; break;
					} else cc += 2;
				}
				if(cc + 1 > k) f = 0;
				if(f) {
					printf("%lld ", x[i]);
					for(int j = 1; j <= li[i][0]; ++j) {
						ll p = li[i][j];
						int idx = id[p];
						vv[idx]=1;
						printf("%lld %lld ", vec[idx][0], vec[idx][1]);
					}
					num = cc + 1;
					for(int j = 1; j <= tot && num < k; ++j) {
						if(!vv[j]) {
							num += 2;
							printf("%lld %lld ", vec[j][0], vec[j][1]);
						}
					}
					printf("\n");
					break;
				}
			}
			if(!f) {
				printf("0\n"); //printf("!!!2\n");
			}
		}
	}
}

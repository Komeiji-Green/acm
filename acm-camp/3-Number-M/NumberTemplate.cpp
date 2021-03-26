#include <iostream>
#include <ctime>
using namespace std;
typedef long long ll;

const int maxn = 1000000 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛法 [1, n] 内素数
void Prime(int n) {
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++) {
            if (1ll * i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

// 线性筛求积性函数
int phi[maxn], mu[maxn], d[maxn], D[maxn], q[maxn];
void Sieve(int n) {
    isnt[1] = true;
    phi[1] = 1;
    //mu[1] = 1;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1; //mu[i] = -1;
            // d[i] = 2; q[i] = 1;
            // D[i] = i + 1; q[i] = 1;
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                phi[x] = phi[i] * prime[j]; // mu[x] = 0;
                // d[x] = d[i] / (q[i] + 1) * (q[i] + 2), q[x] = q[i] + 1;
                // D[x] = D[i] / (prime[j] ^ (q[i] + 1) - 1) * (prime[j] ^ (q[i] + 2) - 1), q[x] = q[i] + 1;
                break;
            } else {
                phi[x] = phi[i] * (prime[j] - 1); // mu[x] = -mu[i]
                // d[x] = 2 * d[i], q[x] = 1;
                // D[x] = (prime[j] + 1) * D[i], q[x] = 1;
            }
        }
    }
}

// 素因数分解 
int p[maxn], l[maxn], cnt2 = 0;
void Fact(int x) {
    cnt2 = 0;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            p[++cnt2] = i; l[cnt2] = 0;
            while(x % i == 0) {
                x /= i; ++l[cnt2];
            }
        }
    }
    if(x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[++cnt2] = x; l[cnt2] = 1;
    }
}

void Fact(ll x, vector<int>& fact) {
    for(ll i = 2; i * i <= x; ++i) {
        if(x % i == 0) {
            fact.push_back(i);
            while(x % i == 0) x /= i; 
        }
    }
    if(x != 1) fact.push_back(x);
}

// 欧拉函数
int euler(int n) {
    Fact(n);
    int ans = n;
    for(int i = 1; i <= cnt2; ++i) {
        ans /= p[i];
        ans *= p[i] -1;
    }
    return ans;
}

// 求模p的乘法逆元 [1, p - 1]
int inv[maxn];
void init() {
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i < N; ++i) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}

// 快速幂 计算 a^k % p
ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

// 慢速乘
ll mul(ll a, ll b, ll mod) {
    ll res = 0;
    while(b > 0) {
        if(b & 1) res = (res+a)%mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

// 单乘法逆元 (mod p)
int Inv(int a, int p) { return Pow(a, p - 2, p); }

struct Matrix {
    int m, n;
    int a[5][5];
    Matrix() {}
    Matrix(int *_li, int _m, int _n) {
        m = _m, n = _n;
        for(int i = 0; i < m; i++) 
            for(int j = 0; j < n; j++)
                a[i][j] = _li[i * n + j];
    }
    Matrix Multi(const Matrix &rhs, int p) {
        Matrix ans;
        ans.m = m;
        ans.n = rhs.n;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < rhs.n; j++) {
                ans.a[i][j] = 0;
                for(int k = 0; k < n; k++)
                    ans.a[i][j] = (1ll * ans.a[i][j] + 1ll * a[i][k] * rhs.a[k][j]) % p;
            }
        return ans;
    }
};
// 矩阵快速幂 (mod p) p <= 1e9
Matrix Pow(Matrix a, int k, int p) {
    int li[4] = {1, 0, 0, 1};
    Matrix ans(li, 2, 2);
    while(k) {
        if(k & 1) ans = ans.Multi(a, p);
        k >>= 1; a = a.Multi(a, p);
    }
    return ans;
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int c;
// ax + by = c, 没开ll
// 扩展欧几里得算法, 有解当且仅当gcd(a, b) | c
// a, b 不全为 0, 返回gcd(a, b)
int exgcd(int a, int b, int &x, int &y) {
    if(b == 0) { x = c / a; y = 0; return a; }
    int ans = exgcd(b, a % b, x, y);
    int xx = x; // xx == x'
    x = y, y = xx - a / b * y;
    return ans;
}

ll c;
// ax + by = c, 开ll
// 扩展欧几里得算法, 有解当且仅当gcd(a, b) | c
// a, b 不全为 0, 返回gcd(a, b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) { x = c / a; y = 0; return a; }
    ll ans = exgcd(b, a % b, x, y);
    ll xx = x; // xx == x'
    x = y, y = xx - a / b * y;
    return ans;
}

// ax + by = (a, b)
ll exgcd(ll a,ll b,ll &x,ll &y) {
    if(!b){ x = 1; y = 0; return a;}
    ll gcd = exgcd(b, a % b, x, y);
    ll tp = x; x = y; y = tp - a / b * y;
    return gcd;
}

// 扩欧求逆元
ll INV(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

// 扩展中国剩余定理，用途：解同余方程组，模可以非质数，可以不两两互质
ll ai[maxn], bi[maxn];  // x ≡ ai(mod bi)
ll excrt(int n)
{
    ll x, y, k;
    ll M = bi[1], ans = ai[1]; //第一个方程的解特判
    for (int i = 2; i <= n; i++)
    {
        ll a = M, b = bi[i], c = (ai[i] - ans % b + b) % b; //ax ≡ c(mod b)
        ll gcd = exgcd(a, b, x, y), bg = b / gcd;
        if (c % gcd != 0)
            return -1; // 判断是否无解

        x = mul(x, c / gcd, bg);
        ans += x * M; // 更新前k个方程组的答案
        M *= bg;      // M为前k个m的lcm
        ans = (ans % M + M) % M;
    }
    return (ans % M + M) % M;
}



// 卢卡斯定理

ll r[maxn]; // 阶乘
ll Com(ll n, ll m, ll p) {
    if(m > n) return 0;
    return r[n] * Pow(r[m], p - 2, p) % p * Pow(r[n - m], p - 2, p) % p;
}
ll lucas(ll n, ll m, ll p) {
    if(!m) return 1;
    return Com(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}

// 扩展卢卡斯定理

// 递归求解(n! / px) mod pk
ll F(ll n, ll p, ll pk) {
    if(n == 0) return 1;
    ll rou = 1; // 循环节
    ll rem = 1; // 余项
    for(ll i = 1; i <= pk; ++i) {
        if(i % p) rou = rou * i % pk;
    }
    rou = Pow(rou, n / pk, pk);
    for(ll i = pk * (n / pk); i <= n; ++i) {
        if(i % p) rem = rem * (i % pk) % pk; // 小心i炸int
    }
    return F(n / p, p, pk) * rou % pk * rem % pk;
}

// 素数p在n!中的次数
ll G(ll n, ll p) {
    if(n < p) return 0;
    return G(n / p, p) + (n / p);
}

ll C_pk(ll n, ll m, ll p, ll pk) {
    ll fz = F(n, p, pk), fm1 = INV(F(m, p, pk), pk), fm2 = INV(F(n - m, p, pk), pk);
    ll mi = Pow(p, G(n, p) - G(m, p) - G(n - m, p), pk);
    return fz * fm1 % pk * fm2 % pk * mi % pk;
}

ll exlucas(ll n, ll m, ll P) {
    Fact(P);
    for(int i = 1; i <= cnt2; ++i) {
        ll pk = 1;
        for(int j = 0; j < l[i]; ++j) {
            pk *= p[i];
        }
        bi[i] = pk, ai[i] = C_pk(n, m, p[i], pk);
    }
    return excrt(cnt2) % P;
}



/*
大数除小数：
a的本值太大无法表示？
(a / b) % p == ( ( a % (b * p) ) / b ) % p;
*/

bool Miller_Rabin(ll x) //判断素数，事先打好素数表
{
    int s = 0; ll t = x - 1;
    if (x == 2) return true;
    if (x < 2 || !(x & 1)) return false; 
    while (!(t & 1)) {   //将x分解成(2^s)*t的样子
        s++; t >>= 1;
    }
    ll k;
    for (int i = 1; i <= 15 && prime[i] < x; ++i) //随便选一个素数进行测试
    {
        ll a = prime[i];
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

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int js;
ll pri[100];
ll Pollard_Rho(ll n)
{
    ll x = rand() % n, y = x, c = rand() % n, QvQ = 2;
    int i = 1;
    while (1)
    {
        ++i, x = (mul(x, x, n) + c) % n; //生成伪随机数
        if (y == x)
            return 1; //兔子追上了乌龟
        ll d = gcd((y - x + n) % n, n);
        if (d > 1)
            return d; //注意，有可能在某个c意义下，d一直都是n
        if (i == QvQ)
            y = x, QvQ <<= 1; //移动乌龟
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

int main() {
    
}

/*
int main()
{
    clock_t st, ed;
    st = clock();

    

    ed = clock();

    Fact(999911658);
    for(int i = 1; i <= cnt2; i++) {
        printf("%d %d\n", p[i], l[i]);
    }

    cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;

}
*/


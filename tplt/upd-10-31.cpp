
// 计算几何
// 扫描线（矩形周长并）

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100050;

int ch[maxn*60][2], tot;
int sum[maxn*60], len[maxn*60];
int lnum[maxn*60], rnum[maxn*60], num[maxn*60];
int root;
void pushup(int k, int l, int r) {
    if(sum[k]) {
        len[k] = r - l + 1;
        lnum[k] = rnum[k] = num[k] = 1;
    }
    else if(l == r) len[k] = lnum[k] = rnum[k] = num[k] = 0;
    else {
        int lch = ch[k][0], rch = ch[k][1];
        len[k] = len[lch] + len[rch];
        num[k] = num[lch] + num[rch] - (rnum[lch] && lnum[rch]);
        lnum[k] = lnum[lch]; rnum[k] = rnum[rch];
    }
}
void add(int &k, int L, int R, int v, int l, int r) {
    if(!k) k = ++tot;
    if(L <= l && r <= R) {
        sum[k] += v;
        pushup(k, l ,r);
    } else {
        int mid = l + ((r - l) >> 1);
        if(L <= mid) add(ch[k][0], L, R, v, l, mid);
        if(R > mid) add(ch[k][1], L, R, v, mid + 1, r);
        pushup(k, l, r);
    }
} 

struct Line {
    ll l, r, h;
    int tag;
    bool operator< (const Line& b) {
        return h < b.h || h == b.h && tag > b.tag;
    }
} lx[maxn], ly[maxn];

const int MAXL = 30000;
ll gao(Line* lx, int m) {
    ll last_h = 0, last_len = 0, last_num = 0;
    ll cur_h = lx[1].h, cur_len, cur_num;
    ll ans = 0;
    for(int i = 1; i <= m; ++i) {
        add(root, lx[i].l, lx[i].r - 1, lx[i].tag, 1, MAXL);
        cur_len = len[root], cur_num = num[root], cur_h = lx[i].h;
        ans += 2 * (cur_h - last_h) * last_num;
        ans += abs(cur_len - last_len);
        last_len = cur_len, last_num = cur_num, last_h = cur_h;
    }
    return ans;
}
int main() {
    int m;
    cin >> m;
    ll x1, y1, x2, y2;
    for(int i = 1; i <= m; ++i) {
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        x1 += 10001; x2 += 10001; y1 += 10001; y2 += 10001;
        lx[i].tag = 1; lx[i].l = x1; lx[i].r = x2; lx[i].h = y1;
        lx[m + i].tag = -1; lx[m + i].l = x1; lx[m + i].r = x2; lx[m + i].h = y2;
        ly[i].tag = 1; ly[i].l = y1; ly[i].r = y2; ly[i].h = x1;
        ly[m + i].tag = -1; ly[m + i].l = y1; ly[m + i].r = y2; ly[m + i].h = x2;
    }
    m = 2 * m;
    sort(lx + 1, lx + m + 1);
    sort(ly + 1, ly + m + 1);
    ll ans = 0;
    ans = gao(lx, m);
    cout << ans << endl;
}


// 数论
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


// 杜教筛

const int maxn = (1 << 21); // n ^ (2/3)
ll sum_mu[maxn];
unordered_map<ll, ll> mp_mu;

// f 的前缀和
ll S_mu(ll x) {
    if(x < maxn) return sum_mu[x];
    if(mp_mu.count(x)) return mp_mu[x];
    ll res = 1; // (f * g) 的 [1, x] 前缀和
    for(ll i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        res -= S_mu(x / i) * (j - i + 1); // sum_g[i, j]
    }
    return mp_mu[x] = res; // 若g(1)非1, 记得除掉
}

ll S_phi(ll x) {
    ll res = 0;
    for(ll i = 1, j; i <= x; i = j + 1) {
        j = x / (x / i);
        res += (S_mu(j) - S_mu(i - 1)) * (x / i) * (x / i);
    }
    return ((res - 1) >> 1) + 1;
}

int main() {
    Sieve(maxn - 1);
    sum_mu[0] = 0;
    for(int i = 1; i < maxn; ++i) {
        sum_mu[i] = sum_mu[i - 1] + mu[i];
    }
    int T;
    cin >> T;
    ll n;
    while(T--) {
        scanf("%lld", &n);
        ll ans1 = S_mu(n), ans2 = S_phi(n);
        printf("%lld %lld\n", ans2, ans1);
    }
}


// 字符串
// SAM

const int maxn = 2000500;   // 字符串长度的两倍
struct Suffix_Automata {
    int trans[maxn][36], len[maxn], link[maxn], tag[maxn], sz, last, lg;
    Suffix_Automata() { sz = 1, last = 1; }
    void setlg(int _lg) { lg = _lg; }
    void extend(int id, int bit) {
        int cur = (++sz), p;
        len[cur] = len[last] + 1;   // len[1] == 0
        tag[cur] = (1 << bit);
        for(p = last; p && !trans[p][id]; p = link[p]) trans[p][id] = cur;
        if(!p) link[cur] = 1;
        else {
            int q = trans[p][id];
            if(len[p] + 1 == len[q]) link[cur] = q;
            else {
                int clone = (++sz);
                len[clone] = len[p] + 1;
                memcpy(trans[clone], trans[q], sizeof(trans[q]));
                link[clone] = link[q];
                for(; p && trans[p][id] == q; p = link[p]) trans[p][id] = clone;
                link[q] = link[cur] = clone;
            }
        }
        last = cur;
    }
    vector<int> G[maxn];
    void dfs(int x) {
        for(auto y : G[x]) {
            dfs(y);
            tag[x] |= tag[y];
        }
    }
    void build() {
        for(int i = 2; i <= sz; ++i) {
            G[link[i]].push_back(i);
        }
        dfs(1);
    }
    int gao() {
        build();
        int ans = 0, uu = (1 << lg);
        for(int x = 1; x <= sz; ++x) {
            if((tag[x] + 1) == uu) ans = max(ans, len[x]);
        }
        return ans;
    }
} T;

// multi_LCS
char s[10][maxn];
int main() {
    int n = 0;
    for(int i = 0; scanf("%s", s[i]) != EOF; ++i) {
        ++n;
        for(int j = 0; ; ++j) {
            if(!s[i][j]) {
                s[i][j] = 'a' + 26 + i;
                s[i][j + 1] = '\0';
                break;
            }
        }
        for(int j = 0; s[i][j]; ++j) {
            T.extend(s[i][j] - 'a', i);
        }
    }
    T.setlg(n);
    printf("%d\n", T.gao());
}


// 图论
// 二分图匹配

#define int long long
const int inf = 1e18;
const int maxn = 509;
int n, m, cost[maxn][maxn], mat[maxn], pre[maxn];
int wisha[maxn], wishb[maxn], va[maxn], vb[maxn], slack[maxn];
void init(int a[], int b) {
	for(int i = 0; i <= n; i++) a[i] = b;
}
void bfs(int u)
{
	init(pre, 0);
	init(slack, inf);
	slack[0] = 0;
	int x = 0, y = 0, yy = 0, delta = 0;
	mat[y] = u; //最开始0匹配u,为什么这么写,无关紧要,总要让一个开头嘛
	while (1) {
		x = mat[y], delta = inf, vb[y] = 1; //现在是帮x找完美匹配
		for (int i = 1; i <= n; i++) {
			if (vb[i]) continue; //本次访问过,不用管了
			if (slack[i] > wisha[x] + wishb[i] - cost[x][i]) {
				slack[i] = wisha[x] + wishb[i] - cost[x][i]; //更新最小误差期望
				pre[i] = y;
			}
			if (slack[i] < delta) delta = slack[i], yy = i; //yy记录谁是最小误差
		}
		//delta是最小的误差,用于调整期望
		for (int i = 0; i <= n; i++) {
			if (vb[i]) wisha[mat[i]] -= delta, wishb[i] += delta;
			else slack[i] -= delta;
		}
		y = yy; //啥意思?yy记录的是最小误差,那么现在修改了期望值,所以可以直接匹配y
		if (mat[y] == -1) break; //直到找到一个人没有匹配
	}
	while (y) mat[y] = mat[pre[y]], y = pre[y];
}
int km() {
	init(wisha, 0);
	init(wishb, 0);
	init(mat, -1);
	for (int i = 1; i <= n; i++) {
		init(vb, 0);
		bfs(i);
	}
	int res = 0;
	for (int i = 1; i <= n; i++) 
		res += cost[mat[i]][i];
	return res;
}
signed main() 
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cost[i][j] = -inf;
	for (int i = 1; i <= m; i++) {
		int l, r, w;
		cin >> l >> r >> w;
		cost[l][r] = max(cost[l][r], w);
	}
	cout << km() << '\n';
	for (int i = 1; i <= n; i++)
		cout << mat[i] << " ";
}
#include<bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;

// ������ ���� a^k % p
int Pow(int a, int k, int p) {
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

const ll mod = 1e9 + 7;
const ll maxa = 200000;
const ll sq = 448;

const int maxn = 1005;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// ����ɸ�� [1, n] ������
void Prime(int n)
{
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

const int N = 100500;

struct Val {
    int p, Prev;
    bool operator< (const Val& b) { return Prev < b.Prev; }
} val[N];
int Q[100][N], t[100][N<<2];
vector<Val> vec[N<<2];
vector<int> pre[N<<2];

void build(int k, int l, int r) {
    int len = r - l + 1;
    vec[k].resize(len);
    pre[k].resize(len);
    if(l == r) {
        vec[k][0] = val[l];
        pre[k][0] = val[l].p;
        for(int i = 1; i <= cnt; ++i) {
            t[i][k] = Q[i][l];
        }
    } else {
        int mid = l + ((r - l) >> 1);
        for(int i = l; i <= r; ++i) {
            vec[k][i-l] = val[i];
        }
        sort(vec[k].begin(), vec[k].end());
        pre[k][0] = vec[k][0].p;
        for(int i = 1; i < len; ++i) {
            pre[k][i] = 1ll * pre[k][i-1] * vec[k][i].p % mod;
        }
        build(k<<1, l, mid);
        build(k<<1|1, mid + 1, r);
        for(int i = 1; i <= cnt; ++i) {
            t[i][k] = max(t[i][k<<1], t[i][k<<1|1]);
        }
    }
}

int query(int L, int R, int k, int l, int r, int* maxl) {
    //printf("%d %d\n", l, r);
    if(L <= l && r <= R) {
        for(int i = 1; i <= cnt; ++i) maxl[i] = t[i][k];
        Val x; x.Prev = L;
        int idx = lower_bound(vec[k].begin(), vec[k].end(), x) - vec[k].begin();
        //printf("%d\n", idx);
        return idx == 0 ? 1 : pre[k][idx-1];
    } else {
        int mid = l + ((r - l) >> 1);
        int res = 1;
        int max_le[100], max_ri[100];
        if(L <= mid)
            res = 1ll * res * query(L, R, k<<1, l, mid, max_le) % mod;
        if(mid < R) 
            res = 1ll * res * query(L, R, k<<1|1, mid + 1, r, max_ri) % mod;
        for(int i = 1; i <= cnt; ++i) {
            maxl[i] = max(max_le[i], max_ri[i]);
        }
        return res;
    }
}
 
int a[N], Prev[N], times[100];


int main() {
    //freopen("FO.txt", "w", stdout);
    memset(t, 0, sizeof(t));
    memset(Q, 0, sizeof(Q));
    Prime(sq);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1, p, l; j <= cnt; ++j) {
            p = prime[j], l = 0;
            while(a[i] % p == 0) {
                a[i] /= p; ++l;
            }
            Q[j][i] = l;
        }
    }
    /*for(int j = 1; j <= cnt; ++j) {
        //printf("%d\t", prime[j]);
    }
    //printf("\n");
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= cnt; ++j) 
            //printf("%d\t", Q[j][i]);
        //printf("\n");
    }*/
    memset(Prev, 0, sizeof(Prev));
    for(int i = 1; i <= n; ++i) {
        val[i].p = a[i];
        val[i].Prev = Prev[a[i]];
        Prev[a[i]] = i;
    }
    build(1, 1, n);
    int q, x, y, last = 0, L, R;
    cin >> q;
    while(q--) {
        scanf("%d %d", &x, &y);
        L = (last + x) % n + 1;
        R = (last + y) % n + 1;
        if(L > R) swap(L, R);
        //printf("%d %d\n", L, R);
        int ans = query(L, R, 1, 1, n, times);
        //printf("%d\n", ans);
        for(int i = 1; i <= cnt; ++i) {
            //printf("%d\t", times[i]);
            ans = 1ll * ans * Pow(prime[i], times[i], mod) % mod;
        }
        //printf("\n");
        ans = (ans + mod) % mod;
        last = ans;
        printf("%d\n", ans);
    }
    return 0;
}

const int MAXLOGN = 20;
const int MAXN = 1 << MAXLOGN;
const int MOD = 998244353;
const int G = 3;

inline int qadd(const int &x, const int &y) {
    int r = x + y;
    return r >= MOD ? r - MOD : r;
}

inline int qsub(const int &x, const int &y) {
    int r = x - y;
    return r < 0 ? r + MOD : r;
}

inline int qmul(const int &x, const int &y) {
    ll r = 1LL * x * y;
    if(r >= MOD)
        r %= MOD;
    return r;
}

int qpow(int x, int n) {
    ll res = 1;
    while(n) {
        if(n & 1)
            res = qmul(res, x);
        x = qmul(x, x);
        n >>= 1;
    }
    return res;
}

using poly_t = int[MAXN];
using poly = int *const;

/* Show h[0...n-1], be careful that the length of h is less than n. */
void polyshow(poly &h, int n) {
    for(int i = 0; i != n; ++i)
        printf("%d%c", h[i], " \n"[i == n - 1]);
}

void FNTT(poly &h, int n, int op) {
    static int gl[MAXLOGN], rev[MAXN], revl;
    if(gl[0] == 0) {
        for(int l = 0; l < MAXLOGN; ++l)
            gl[l] = qpow(G, (MOD - 1) / (1 << (l + 1)));
    }
    if((1 << revl) != n) {
        for(revl = 0; (1 << revl) != n; ++revl);
        for(int i = 0; i < n; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (revl - 1));
    }
    for(int i = 0; i < n; ++i) {
        if(i < rev[i])
            swap(h[i], h[rev[i]]);
    }
    for(int l = 0, len; (len = 1 << l) < n; ++l) {
        for(int i = 0, Gl = gl[l]; i < n; i += (len << 1)) {
            for(int j = i, w = 1; j < i + len; ++j, w = qmul(w, Gl)) {
                int u = h[j], t = qmul(h[j + len], w);
                h[j] = qadd(u, t), h[j + len] = qsub(u, t);
            }
        }
    }
    if(op == -1) {
        reverse(h + 1, h + n);
        for(int i = 0, inv = qpow(n, MOD - 2); i < n; ++i)
            h[i] = qmul(h[i], inv);
    }
}

/* Enlarge n to the smallest power of 2. */
void pretreat(poly &h, int &n) {
    int tn = 1;
    while(tn < n)
        tn <<= 1;
    fill(h + n, h + tn, 0);
    n = tn;
}

/* Add h1 and h2, and store the result in f. */
int polyadd(poly &h1, int n1, poly &h2, int n2, poly &f) {
    int n = max(n1, n2);
    fill(h1 + n1, h1 + n, 0);
    fill(h2 + n2, h2 + n, 0);
    for(int i = 0; i != n; ++i)
        f[i] = qadd(h1[i], h2[i]);
    return n;
}

/* Substract h2 from h1, and store the result in f. */
int polysub(poly &h1, int n1, poly &h2, int n2, poly &f) {
    int n = max(n1, n2);
    fill(h1 + n1, h1 + n, 0);
    fill(h2 + n2, h2 + n, 0);
    for(int i = 0; i != n; ++i)
        f[i] = qsub(h1[i], h2[i]);
    return n;
}

/* Multiply h1 and h2, and store the result in f. */
int polymul(poly &h1, int n1, poly &h2, int n2, poly &f) {
    int n = n1 + n2 - 1, tn = 1;
    while(tn < n)
        tn <<= 1;
    fill(h1 + n1, h1 + tn, 0), FNTT(h1, tn, 1);
    fill(h2 + n2, h2 + tn, 0), FNTT(h2, tn, 1);
    for(int i = 0; i != tn; ++i)
        f[i] = qmul(h1[i], h2[i]);
    FNTT(f, tn, -1);
    return n;
}

/* The following methods are solved in the sense of modulo x^n */

/* Get the inverse of h, and store the result in f. */
void polyinv(poly &h, int n, poly &f) {
    pretreat(h, n);
    static poly_t tmp;
    fill(f, f + n + n, 0), f[0] = qpow(h[0], MOD - 2);
    for(int t = 2; t <= n; t <<= 1) {
        copy(h, h + t, tmp), fill(tmp + t, tmp + t + t, 0);
        FNTT(f, t + t, 1), FNTT(tmp, t + t, 1);
        for(int i = 0; i != t + t; ++i)
            f[i] = qmul(f[i], qsub(2, qmul(f[i], tmp[i])));
        FNTT(f, t + t, -1);
        fill(f + t, f + t + t, 0);
    }
}

/* Get the derivative of h, and store the result in f. */
void polyder(poly & h, int n, poly & f) {
    for(int i = 1; i != n; ++i)
        f[i - 1] = qmul(h[i], i);
    f[n - 1] = 0;
}

/* Get the integral of h, and store the result in f. */
void polyint(poly &h, int n, poly &f, int C = 0) {
    static int inv[MAXN];
    if(inv[0] == 0) {
        inv[1] = 1;
        for(int i = 2; i < MAXN; ++i)
            inv[i] = qmul(inv[MOD % i], (MOD - MOD / i));
        inv[0] = -1;
    }
    for(int i = n - 1; i != 0; --i)
        f[i] = qmul(h[i - 1], inv[i]); /* or inv[i] = qpow(i, MOD - 2) */
    f[0] = C; /* constant C */
}

/* Get the logarithm of h, and store the result in f. */
void polylog(poly &h, int n, poly & f) {
    pretreat(h, n);
    static poly_t tmp;
    polyder(h, n, tmp), polyinv(h, n, f);
    fill(tmp + n, tmp + n + n, 0);
    FNTT(tmp, n + n, 1), FNTT(f, n + n, 1);
    for(int i = 0; i != n + n; ++i)
        tmp[i] = qmul(tmp[i], f[i]);
    FNTT(tmp, n + n, -1);
    polyint(tmp, n, f);
}

/* Get the exponent of h, and store the result in f. */
void polyexp(poly & h, int n, poly & f) {
    pretreat(h, n);
    static poly_t tmp;
    fill(f, f + n + n, 0), f[0] = 1;
    for(int t = 2; t <= n; t <<= 1) {
        polylog(f, t, tmp);
        tmp[0] = qsub(qadd(h[0], 1), tmp[0]);
        for(int i = 1; i != t; ++i)
            tmp[i] = qsub(h[i], tmp[i]);
        fill(tmp + t, tmp + t + t, 0);
        FNTT(f, t + t, 1), FNTT(tmp, t + t, 1);
        for(int i = 0; i != t + t; ++i)
            f[i] = qmul(f[i], tmp[i]);
        FNTT(f, t + t, -1);
        fill(f + t, f + t + t, 0);
    }
}

void polypow1(poly &h, int n, int k1, int k2, poly &f) {
    static poly_t tmp;
    polylog(h, n, tmp);
    for(int i = 0; i != n; ++i)
        tmp[i] = qmul(tmp[i], k1);
    polyexp(tmp, n, f);
}

void polypow2(poly &h, int n, int k1, int k2, poly &f) {
    for(int i = 0, invh = qpow(h[0], MOD - 2); i != n; ++i)
        f[i] = qmul(h[i], invh);
    polypow1(h, n, k1, k2, f);
    for(int i = 0, hk = qpow(h[0], k2); i != n; ++i)
        f[i] = qmul(f[i], hk);
}

/*  Get the power k of h, and store the result in f.
    k1 = k mod MOD, k2 = k mod (MOD - 1), k = true k */
void polypow(poly &h, int n, int k1, int k2, int k, poly &f) {
    int t = 0;
    for(; t < n && h[t] == 0; ++t);
    if(1LL * k * t >= n)
        fill(f, f + n, 0);
    else {
        static poly_t tmp;
        for(int i = 0; i + t != n; ++i)
            tmp[i] = h[i + t];
        fill(tmp + n - t, tmp + n, 0);
        polypow2(tmp, n, k1, k2, f);
        for(int i = n - 1; i >= k * t; --i)
            f[i] = f[i - k * t];
        fill(f, f + k * t, 0);
    }
}

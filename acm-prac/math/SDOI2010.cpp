// SDOI2010

const ll MOD = 999911659;
const ll PHI = 999911658;

ll gao(ll n, ll m, ll P) {
    for(int i = 1; i <= cnt2; ++i) {
        bi[i] = p[i];
        ai[i] = lucas(n, m, p[i]);
    }
    return excrt(cnt2) % P;
}


int main() {
    Fact(PHI);
    r[0] = 1;
    for(ll i = 1; i <= p[cnt2]; ++i) {
        r[i] = r[i - 1] * i % PHI;
    }
    ll n, g;
    cin >> n >> g;
    ll k = 1, ans = 0;
    for(k = 1; k * k < n; ++k) {
        if(n % k == 0) {
            ans = (ans + gao(n, k, PHI)) % PHI;
            ans = (ans + gao(n, n / k, PHI)) % PHI;
        }
    }
    if(k * k == n) ans = (ans + gao(n, k, PHI)) % PHI;
    ans = (ans + PHI) % PHI + PHI;
    ans = Pow(g, ans, MOD);
    printf("%lld\n", (ans + MOD) % MOD);
}

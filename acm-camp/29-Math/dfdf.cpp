int p[maxn], l[maxn], k = 0;
void Fact(int x) {
    k = 0;
    for(int i = 2; i * i <= x; i++)
        if(x % i == 0) {
            p[++k] = i; l[k] = 0;
            while(x % i == 0) {
                x /= i; ++l[k];
            }
        }
    if(x != 1) {  // 此时x一定是素数， 且为原本x的大于根号x的唯一素因子
        p[++k] = x; l[k] = 1;
    }
}

typedef long long ll;
int main() {
    const int mod = 1e9 + 7;
    int x, y;
    int z = x * y % mod; //溢出
    int w = 1ll * x * y % mod; //可以
    ll x, y;
    ll ans = x * y % mod;   //可以
}

void Sieve(int n) {
    isnt[1] = true, phi[1] = 1, cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            //1
        }
        for(j) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                //2
                break;
            } else {
                //3
            }
        }
    }
}
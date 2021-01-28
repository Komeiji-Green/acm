#include <iostream>
#include <ctime>
using namespace std;
typedef long long ll;

const int maxn = 100000;
int p[maxn]; // 素因子
int l[maxn]; // 重数
int cnt = 0;

// 素因数分解 
void Fact(int x) 
{
    cnt = 0;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            p[++cnt] = i; l[cnt] = 0;
            while(x % i == 0) {
                x /= i; 
                l[cnt]++;
            }
        }
    }
    if(x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[++cnt] = x; l[cnt] = 1;
    }
}

int fac[maxn];
int tot = 0;

void FactList(int x) {
    int i = 1;
    tot = 0;
    for(i = 1; i * i < x; i++) {
        if(x % i == 0) {
            fac[++tot] = i;
            fac[++tot] = x / i;
        }
    }
    if(i * i == x) fac[++tot] = i;
}

// 需要Fact处理好全体质因子
int Phi(int x) {
    int ans = x;
    for(int i = 1; i <= cnt; i++) {
        if(x % p[i] == 0) {
            ans = ans / p[i] * (p[i] - 1);
        }
    }
    return ans;
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int x, M;
        scanf("%d %d", &x, &M);
        Fact(x);    // 质因数分解
        FactList(x);    // 获取全体约数
        int ans = 0;
        for(int i = 1; i <= tot; i++) {
            int m = x / fac[i];
            if(m < M) continue;
            int phi = Phi(fac[i]);
            ans += phi;
            //printf("%d %d\n", fac[i], phi);
        }
        printf("%d\n", ans);
    }
}
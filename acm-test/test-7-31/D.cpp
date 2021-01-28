#include<iostream>
using namespace std;
typedef long long ll;

const int maxn = 100;

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

ll A, B;
int N;

// 单个个数
ll L(int p) {
    if(A % p == 0)
        return B / p - A / p + 1;
    else
        return B / p - A / p;
}


int main()
{
    int T;
    cin >> T;
    for(int test = 1; test <= T; test++) {
        cnt = 0;
        cin >> A >> B >> N;
        Fact(N);
        ll ans = 0;
        for(int i = 0; i < (1 << cnt); i++) {
            int s = 0;  // 有多少因子
            int x = 1;  // 因子乘积
            for(int j = 0; j < cnt; j++) {
                if(i & (1 << j)) {
                    s++;
                    x *= p[j + 1];
                }
            }
            ans += s % 2 ? -L(x) : L(x);
        }
        printf("Case #%d: ", test);
        cout << ans << endl;
    }
}
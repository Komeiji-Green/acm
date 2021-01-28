#include <iostream>
#include <ctime>
using namespace std;
typedef long long ll;

const int maxn = 1000000 + 500;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛法 [1, n] 内素数
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

ll func[maxn];
int phi[maxn];

// 线性筛求积性函数
void Phi(int n) {
    isnt[1] = true;
    phi[1] = 1;
    func[1] = 1;
    //mu[1] = 1;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
            func[i] = 1ll * phi[1] + 1ll * i * phi[i];
            //mu[i] = -1;
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                phi[x] = phi[i] * prime[j];
                int y = x;
                int q = 1;
                while(y % prime[j] == 0) {
                    y /= prime[j];
                    q *= prime[j];
                }
                func[x] = func[i] + 1ll * q * phi[q] * func[y]; 
                break;
            } else {
                phi[x] = phi[i] * (prime[j] - 1);
                func[x] = func[i] + 1ll * prime[j] * phi[prime[j]] * func[i];
            }
        }
    }
}


// sum d * phi(d) (d | n)

int main()
{
    int T;
    cin >> T;

    //clock_t st, ed;
    //st = clock();
    Phi(1000000);
    //ed = clock();
    //cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
    /*for(int i = 1; i <= 50; i++) {
        printf("%d phi: %d, func: %lld\n", i, phi[i], func[i]);
    }*/
    while(T--) {
        int x;
        scanf("%d", &x);
        ll ans = (func[x] - 1) * x / 2 + x;
        printf("%lld\n", ans);
    }
}
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


int main()
{
    int n;
    cin >> n;
    Fact(n);

    ll ans = 1;
    for(int i = 1; i <= cnt; i++) {
        ans *= l[i] + 1;
    }
    ans -= 1;
    cout << ans << endl;
}